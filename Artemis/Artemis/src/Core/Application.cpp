#include "Application.h"

Application* Application::Create()
{
	return new Application();
}

void Application::Run()
{

	while (m_Open) {



	}

}

void Application::Terminate(Application* application)
{
	delete application;
}


