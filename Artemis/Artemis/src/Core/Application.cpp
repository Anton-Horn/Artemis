#include "Application.h"
#include "Log.h"

#include "Debug_Test.h"

#include "Input.h"

Application* Application::s_instance;

void Application::Run()
{

	WindowSpecification window_spec;
	window_spec.width = 800;
	window_spec.height = 600;
	window_spec.title = "Artemis";

	m_window.Create(window_spec);

	m_input.Init();

	m_renderer2d.Init(RenderingAPI::OpenGL);

	m_post_renderer.Init(RenderingAPI::OpenGL);
	
	while (m_window.Open()) {

		m_renderer2d.Test();
		m_post_renderer.DrawFrameBufferColorAttachment(m_renderer2d.GetFrameBuffer());
		m_window.Update();
	}

}

void Application::Terminate()
{
	m_post_renderer.Terminate();
	m_renderer2d.Terminate();
	m_window.Terminate();
}

Window& Application::GetWindow()
{
	return s_instance->m_window;
}

Input& Application::GetInput()
{
	return s_instance->m_input;
}

Renderer2d& Application::GetRenderer2d()
{
	return s_instance->m_renderer2d;
}

Application* Application::Create()
{
	s_instance = new Application();
	return s_instance;
}


