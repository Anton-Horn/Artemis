
#include "Application.h"

int main(int argc, char** argv) {

	bool stay_open = false;

	do {
		Application* app = Application::Create();
		if (!app) return -1;

		app->Run();
		stay_open = Application::Terminate(app);
	} 
	while (stay_open);

	return 0;
}

