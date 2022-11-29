#pragma once

#include "Core/Core.h"
#include <vector>

#include "Color.h"

enum class FramebufferTextureFormat {
	None = 0,

	RGBA8,

	RED_INTEGER,

	DEPTH24STENCIL8,
	Depth = DEPTH24STENCIL8,
};

struct FramebufferTextureSpecification {
	FramebufferTextureFormat format;
	FramebufferTextureSpecification() = default;
	FramebufferTextureSpecification(FramebufferTextureFormat format) : format(format) {};
};

struct FramebufferTextureAttachmentSpecification {
	std::vector<FramebufferTextureSpecification> texture_attachments;
	FramebufferTextureAttachmentSpecification() = default;
	FramebufferTextureAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) : texture_attachments(attachments) {};
};

struct FrameBufferSpecification {

	uint32_t width;
	uint32_t height;
	uint32_t min_width;
	uint32_t max_width;
	uint32_t min_height;
	uint32_t max_height;

	FramebufferTextureAttachmentSpecification attachments;

	uint32_t samples;

	bool swap_chain_target = false;
};

enum class RenderingAPI;

class FrameBuffer
{
public:

	virtual ~FrameBuffer() = default;

	virtual void Bind() = 0;
	virtual void UnBind() = 0;

	virtual uint32_t GetColorAttachmentRendererID(int id) = 0;

	virtual void Resize(uint32_t width, uint32_t height) = 0;

	virtual const FrameBufferSpecification& GetSpec() const = 0;
	virtual FrameBufferSpecification& GetSpec() = 0;

	virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0; 

	static FrameBuffer* Create(const FrameBufferSpecification& spec, RenderingAPI api);

	virtual void ClearColorAttachment(uint32_t index, int value) = 0;
	virtual void ClearColorAttachment(uint32_t index, const Color& color) = 0;

};


