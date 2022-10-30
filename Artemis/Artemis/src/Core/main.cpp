#include <iostream>
#include "Application.h"

#include "Log.h"

int main(int argc, char** argv) {

	bool stay_open = false;

	do {
		Application* app = Application::Create();
		app->Run();
		stay_open = Application::Terminate(app);
	} 
	while (stay_open);

	return 0;
}

