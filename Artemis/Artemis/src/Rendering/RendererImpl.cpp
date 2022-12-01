#include "RendererImpl.h"

#include "OpenGL/OpenGLRenderer.h"

std::shared_ptr<RendererImpl> RendererImpl::Create(RenderingAPI api)
{

	if (api == RenderingAPI::OpenGL) {
		return std::make_shared<OpenGLRenderer>();
	}

	return nullptr;
}