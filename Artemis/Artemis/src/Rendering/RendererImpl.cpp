#include "RendererImpl.h"

#include "OpenGL/OpenGLRenderer.h"

RendererImpl* RendererImpl::Create(RenderingAPI api)
{

	if (api == RenderingAPI::OpenGL) {
		return new OpenGLRenderer();
	}

	return nullptr;
}