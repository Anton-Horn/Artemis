#include "Application.h"
#include "Log.h"

#include "Debug_Test.h"

Application* Application::s_Instance;

void Application::Run()
{

	WindowSpecification window_spec;
	window_spec.width = 800;
	window_spec.height = 600;
	window_spec.title = "Artemis";

	m_Window.Create(window_spec);

	while (m_Window.Open()) {

		m_Window.Update();

	}

}

void Application::Terminate()
{

	m_Window.Terminate();
}

Window& Application::GetWindow()
{
	return s_Instance->m_Window;
}

Application* Application::Create()
{
	s_Instance = new Application();
	return s_Instance;
}


