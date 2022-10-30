#include <iostream>
#include "Application.h"

int main(int argc, char** argv) {

	std::cout << "Hello from Artemis!";

	Application* app = Application::Create();
	app->Run();
	Application::Terminate(app);

	return 0;
}

