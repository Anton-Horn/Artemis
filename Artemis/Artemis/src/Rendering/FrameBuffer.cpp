
#include "FrameBuffer.h"

#include "RenderingPipeline.h"
#include "Rendering\OpenGL\OpenGLFrameBuffer.h"

Ref<FrameBuffer>FrameBuffer::Create(const FrameBufferSpecification& spec)
{
	
	if (RenderingPipeline::GetData().API == RenderingAPI::OpenGL) {
		return CreateRef<FrameBuffer>(spec);
	}
	return nullptr;
}
