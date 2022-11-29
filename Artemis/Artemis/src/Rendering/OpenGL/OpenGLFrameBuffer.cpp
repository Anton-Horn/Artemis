#include "OpenGLFrameBuffer.h"


#include "Core\Log.h"
#include "glad\glad.h"

#include "Core/Debug_Test.h"


static GLenum TextureTarget(bool multisampled)
{
	return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
{
	glCreateTextures(TextureTarget(multisampled), count, outID);
}

static void BindTexture(bool multisampled, uint32_t id)
{
	glBindTexture(TextureTarget(multisampled), id);
}

static void AttachColorTexture(uint32_t id, int samples, GLenum internal_format, GLenum format, uint32_t width, uint32_t height, int index)
{
	bool multisampled = samples > 1;
	if (multisampled)
	{
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internal_format, width, height, GL_FALSE);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
}

static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
{
	bool multisampled = samples > 1;
	if (multisampled)
	{
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
	}
	else
	{
		glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
}

static bool IsDepthFormat(FramebufferTextureFormat format) {
	switch (format)
	{
	case FramebufferTextureFormat::DEPTH24STENCIL8: return true;
	}
	return false;
}


OpenGLFrameBuffer::OpenGLFrameBuffer(FrameBufferSpecification spec)
{
	m_specification = spec;

	for (auto spec : m_specification.attachments.texture_attachments)
	{
		if (!IsDepthFormat(spec.format))
			m_color_attachment_specifications.emplace_back(spec);
		else
			m_depth_attachment_specification = spec;
	}

	Invalidate();
}

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
	glDeleteFramebuffers(1, &m_frame_buffer_id);
	glDeleteTextures((GLsizei)m_color_attachments.size(), m_color_attachments.data());
	glDeleteTextures(1, &m_depth_attachment);
}

void OpenGLFrameBuffer::Invalidate()
{

	if (m_frame_buffer_id) {
		glDeleteFramebuffers(1, &m_frame_buffer_id);
		glDeleteTextures((GLsizei)m_color_attachments.size(), m_color_attachments.data());
		glDeleteTextures(1, &m_depth_attachment);

		m_color_attachments.clear();
		m_depth_attachment = 0;
	}


	glCreateFramebuffers(1, &m_frame_buffer_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_id);

	bool multisample = m_specification.samples > 1;

	// Attachments
	if (m_color_attachment_specifications.size())
	{
		m_color_attachments.resize(m_color_attachment_specifications.size());
		CreateTextures(multisample, m_color_attachments.data(), (uint32_t) m_color_attachments.size());

		for (int i = 0; i < m_color_attachments.size(); i++)
		{
			BindTexture(multisample, m_color_attachments[i]);
			switch (m_color_attachment_specifications[i].format)
			{
			case FramebufferTextureFormat::RGBA8:
				AttachColorTexture(m_color_attachments[i], m_specification.samples, GL_RGBA8, GL_RGBA, m_specification.width, m_specification.height, i);
				break;
			case FramebufferTextureFormat::RED_INTEGER:
				AttachColorTexture(m_color_attachments[i], m_specification.samples, GL_R32I, GL_RED_INTEGER, m_specification.width, m_specification.height, i);
				break;
			}
		}
	}

	if (m_depth_attachment_specification.format != FramebufferTextureFormat::None)
	{
		CreateTextures(multisample, &m_depth_attachment, 1);
		BindTexture(multisample, m_depth_attachment);
		switch (m_depth_attachment_specification.format)
		{
		case FramebufferTextureFormat::DEPTH24STENCIL8:
			AttachDepthTexture(m_depth_attachment, m_specification.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_specification.width, m_specification.height);
			break;
		}
	}

	if (m_color_attachments.size() > 1)
	{
		ART_ASSERT(m_color_attachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers( (uint32_t) m_color_attachments.size(), buffers);
	}
	else if (m_color_attachments.empty())
	{
		// Only depth-pass
		glDrawBuffer(GL_NONE);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		ART_ABORT("FrameBuffer was not complete");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_id);
	glViewport(0, 0, m_specification.width, m_specification.height);
}

void OpenGLFrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const FrameBufferSpecification& OpenGLFrameBuffer::GetSpec() const
{
	return m_specification;
}

FrameBufferSpecification& OpenGLFrameBuffer::GetSpec()
{
	return m_specification;
}

uint32_t OpenGLFrameBuffer::GetColorAttachmentRendererID(int id)
{
	ART_ASSERT_S(id < m_color_attachments.size());
	return m_color_attachments[id];
}

void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
{
	if (width < m_specification.min_width || width > m_specification.max_width) { ART_WARN("[FrameBuffer] Tried to resize the Framebuffer over the min/max Width"); return; }
	if (height < m_specification.min_height || height > m_specification.max_height) { ART_WARN("[FrameBuffer] Tried to resize the Framebuffer over the min/max Height"); return; }

	m_specification.width = width;
	m_specification.height = height;

	glViewport(0, 0, width, height);
	Invalidate();
}

int OpenGLFrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
{
	ART_ASSERT(attachmentIndex < m_color_attachments.size());
	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
	int pixelData;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
	return pixelData;
}

void OpenGLFrameBuffer::ClearColorAttachment(uint32_t index, int value)
{
	ART_ASSERT_S(index < m_color_attachments.size());

	auto& spec = m_color_attachment_specifications[index];

	if (spec.format == FramebufferTextureFormat::RED_INTEGER) {
		glClearTexImage(m_color_attachments[index], 0, GL_RED_INTEGER, GL_INT, &value);
	}
	else {
		ART_ABORT("Tried to clear a non integer colorattachment with an int!");
	}
}

void OpenGLFrameBuffer::ClearColorAttachment(uint32_t index, const Color& color)
{

	ART_ASSERT_S(index < m_color_attachments.size());

	auto& spec = m_color_attachment_specifications[index];

	if (spec.format == FramebufferTextureFormat::RGBA8) {
		glClearTexImage(m_color_attachments[index], 0, GL_RGBA, GL_FLOAT, &color);
	}
	else {
		ART_ABORT("Tried to clear a non integer colorattachment with an int!");
	}

}


