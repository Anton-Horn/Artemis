#pragma once

#include "Window.h"
#include "Input.h"
#include "Rendering/Renderer2d.h"
#include "Rendering/PostRenderer.h"

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
	static Input& GetInput();
	static Renderer2d& GetRenderer2d();

private:

	Window m_window;
	Renderer2d m_renderer2d;
	Input m_input;
	PostRenderer m_post_renderer;

	static Application* s_instance;

};


