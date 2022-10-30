#include "Application.h"
#include "Log.h"

Application* Application::Create()
{
	Log::Create();
	return new Application();
}

void Application::Run()
{

	ART_LOG("TestLog");
	ART_ERROR("Test Error");
	ART_WARN("Test Warn");

	m_Restart = true;
	while (m_Open) {



	}

}

bool Application::Terminate(Application* application)
{
	Log::Delete();
	bool restart = application->m_Restart;
	delete application;
	return restart;
}


