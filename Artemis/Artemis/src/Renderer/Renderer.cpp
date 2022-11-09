#include "Renderer.h"

#ifdef ART_WINDOWS
#include <Windows.h>
#endif

#include "OpenGL/OpenGLRenderer.h"

void Renderer::Create(const RendererSpecification& spec) 
{

	if (spec.rendering_api == RenderingApi::OpenGL) {

		m_RendererImpl = new OpenGLRenderer();
		m_RendererImpl->Create();

	}
 
}
