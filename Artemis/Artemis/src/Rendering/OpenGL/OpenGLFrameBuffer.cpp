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
	m_Specification = spec;

	for (auto spec : m_Specification.Attachments.TextureAttachments)
	{
		if (!IsDepthFormat(spec.Format))
			m_ColorAttachmentSpecifications.emplace_back(spec);
		else
			m_DepthAttachmentSpecification = spec;
	}

	Invalidate();
}

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
	glDeleteFramebuffers(1, &m_FrameBufferID);
	glDeleteTextures((GLsizei)m_ColorAttachments.size(), m_ColorAttachments.data());
	glDeleteTextures(1, &m_DepthAttachment);
}

void OpenGLFrameBuffer::Invalidate()
{

	if (m_FrameBufferID) {
		glDeleteFramebuffers(1, &m_FrameBufferID);
		glDeleteTextures((GLsizei)m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);

		m_ColorAttachments.clear();
		m_DepthAttachment = 0;
	}


	glCreateFramebuffers(1, &m_FrameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

	bool multisample = m_Specification.Samples > 1;

	// Attachments
	if (m_ColorAttachmentSpecifications.size())
	{
		m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
		CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());

		for (size_t i = 0; i < m_ColorAttachments.size(); i++)
		{
			BindTexture(multisample, m_ColorAttachments[i]);
			switch (m_ColorAttachmentSpecifications[i].Format)
			{
			case FramebufferTextureFormat::RGBA8:
				AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, i);
				break;
			case FramebufferTextureFormat::RED_INTEGER:
				AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, i);
				break;
			}
		}
	}

	if (m_DepthAttachmentSpecification.Format != FramebufferTextureFormat::None)
	{
		CreateTextures(multisample, &m_DepthAttachment, 1);
		BindTexture(multisample, m_DepthAttachment);
		switch (m_DepthAttachmentSpecification.Format)
		{
		case FramebufferTextureFormat::DEPTH24STENCIL8:
			AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
			break;
		}
	}

	if (m_ColorAttachments.size() > 1)
	{
		ART_ASSERT(m_ColorAttachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(m_ColorAttachments.size(), buffers);
	}
	else if (m_ColorAttachments.empty())
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
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
	glViewport(0, 0, m_Specification.Width, m_Specification.Height);
}

void OpenGLFrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const FrameBufferSpecification& OpenGLFrameBuffer::GetSpec() const
{
	return m_Specification;
}

FrameBufferSpecification& OpenGLFrameBuffer::GetSpec()
{
	return m_Specification;
}

uint32_t OpenGLFrameBuffer::GetColorAttachmentRendererID(int id)
{
	ART_ASSERT(id < m_ColorAttachments.size());
	return m_ColorAttachments[id];
}

void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
{
	if (width < m_Specification.MinWidth || width > m_Specification.MaxWidth) { ART_WARN("[FrameBuffer] Tried to resize the Framebuffer over the min/max Width"); return; }
	if (height < m_Specification.MinHeight || height > m_Specification.MaxHeight) { ART_WARN("[FrameBuffer] Tried to resize the Framebuffer over the min/max Height"); return; }

	m_Specification.Width = width;
	m_Specification.Height = height;

	glViewport(0, 0, width, height);
	Invalidate();
}

int OpenGLFrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
{
	ART_ASSERT(attachmentIndex < m_ColorAttachments.size());
	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
	int pixelData;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
	return pixelData;
}

void OpenGLFrameBuffer::ClearColorAttachment(uint32_t index, int value)
{
	ART_ASSERT(index < m_ColorAttachments.size());

	auto& spec = m_ColorAttachmentSpecifications[index];

	if (spec.Format == FramebufferTextureFormat::RED_INTEGER) {
		glClearTexImage(m_ColorAttachments[index], 0, GL_RED_INTEGER, GL_INT, &value);
	}
	else {
		ART_ABORT("Tried to clear a non integer colorattachment with an int!");
	}
}


