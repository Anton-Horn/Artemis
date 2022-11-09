
#include "Application.h"

#include "Log.h"
#include "Debug_Test.h"

int main(int argc, char** argv) {

	Log::Create();

	Application* app = Application::Create();
	ART_ASSERT(app);
	app->Run();
	app->Terminate();
	delete app;

	Log::Delete();

	return 0;
}

