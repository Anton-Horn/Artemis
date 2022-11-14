#pragma once

#include "Core/Core.h"

#include <vector>

enum class FramebufferTextureFormat {
	None = 0,

	RGBA8,

	RED_INTEGER,

	DEPTH24STENCIL8,
	Depth = DEPTH24STENCIL8,
};

struct FramebufferTextureSpecification {
	FramebufferTextureFormat Format;
	FramebufferTextureSpecification() = default;
	FramebufferTextureSpecification(FramebufferTextureFormat format) : Format(format) {};
};

struct FramebufferTextureAttachmentSpecification {
	std::vector<FramebufferTextureSpecification> TextureAttachments;
	FramebufferTextureAttachmentSpecification() = default;
	FramebufferTextureAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) : TextureAttachments(attachments) {};
};

struct FrameBufferSpecification {

	uint32_t Width;
	uint32_t Height;
	uint32_t MinWidth;
	uint32_t MaxWidth;
	uint32_t MinHeight;
	uint32_t MaxHeight;

	FramebufferTextureAttachmentSpecification Attachments;

	uint32_t Samples;

	bool SwapChainTarget = false;
};

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

	static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);

	virtual void ClearColorAttachment(uint32_t index, int value) = 0;

};


