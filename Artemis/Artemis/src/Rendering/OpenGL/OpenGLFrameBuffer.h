#pragma once

#include "Rendering\FrameBuffer.h"

class OpenGLFrameBuffer : public FrameBuffer
{

public:

	OpenGLFrameBuffer(FrameBufferSpecification spec);
	~OpenGLFrameBuffer();

	void Invalidate();

private:

	FrameBufferSpecification m_specification;
	uint32_t m_frame_buffer_id = 0;

	std::vector<FramebufferTextureSpecification> m_color_attachment_specifications;
	FramebufferTextureSpecification m_depth_attachment_specification = FramebufferTextureFormat::None;

	std::vector<uint32_t> m_color_attachments;
	uint32_t m_depth_attachment = 0;

	virtual void Bind() override;

	virtual void UnBind() override;

	virtual const FrameBufferSpecification& GetSpec() const override;

	virtual FrameBufferSpecification& GetSpec() override;

	virtual uint32_t GetColorAttachmentRendererID(int id) override;

	virtual void Resize(uint32_t width, uint32_t height) override;

	virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

	virtual void ClearColorAttachment(uint32_t index, int value) override;


	// Geerbt über FrameBuffer
	virtual void ClearColorAttachment(uint32_t index, const Color& color) override;

};


