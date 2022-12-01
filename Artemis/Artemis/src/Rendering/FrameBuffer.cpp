
#include "FrameBuffer.h"
#include "Rendering\OpenGL\OpenGLFrameBuffer.h"

std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec, RenderingAPI api)
{
	
	if (api == RenderingAPI::OpenGL) {
		return std::make_shared<OpenGLFrameBuffer>(spec);
	}
	return nullptr;
}

