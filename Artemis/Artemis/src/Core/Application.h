#pragma once

#include "Window.h"
#include "Rendering/Renderer.h"

class Application {

public:

	Application() = default;

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	Application(const Application&&) = delete;
	Application& operator=(const Application&&) = delete;

	static Application* Create();
		
	void Run();
	void Terminate();

	static Window& GetWindow();

private:

	Window m_Window;
	
	static Application* s_Instance;

};


