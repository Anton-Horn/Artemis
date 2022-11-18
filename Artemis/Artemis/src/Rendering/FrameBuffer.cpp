
#include "FrameBuffer.h"
#include "Rendering\OpenGL\OpenGLFrameBuffer.h"

FrameBuffer* FrameBuffer::Create(const FrameBufferSpecification& spec, RenderingAPI api)
{
	
	if (api == RenderingAPI::OpenGL) {
		return new OpenGLFrameBuffer(spec);
	}
	return nullptr;
}
