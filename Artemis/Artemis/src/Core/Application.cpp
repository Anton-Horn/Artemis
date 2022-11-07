#include "Application.h"
#include "Log.h"

#include "Debug_Test.h"

Application* Application::Create()
{
	Log::Create();
	return new Application();
}

void Application::Run()
{

	ART_ASSERT(true);

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


