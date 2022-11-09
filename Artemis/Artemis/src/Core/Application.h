#pragma once

#include "Window.h"
#include "Renderer/Renderer.h"

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

private:

	Window m_Window;
	Renderer m_Renderer;

};


