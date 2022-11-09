#include "Application.h"
#include "Log.h"

#include "Debug_Test.h"

Application* Application::Create()
{
	return new Application();
}

void Application::Run()
{

	WindowSpecification window_spec;
	window_spec.width = 800;
	window_spec.height = 600;
	window_spec.title = "Artemis";

	m_Window.Create(window_spec);

	RendererSpecification renderer_spec;
	renderer_spec.rendering_api = RenderingApi::OpenGL;

	m_Renderer.Create(renderer_spec);

	while (m_Window.Open()) {

		m_Window.Update();

	}

}

void Application::Terminate()
{

	m_Window.Terminate();
}


