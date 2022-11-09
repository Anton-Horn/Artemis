#pragma once

#include <stdint.h>
#include <string>

struct WindowSpecification {

	uint32_t width;
	uint32_t height;

	std::string title;

};

class Window {

public:

	void Create(const WindowSpecification& spec);
	void Terminate();

	void Update();

	bool Open();

	Window() = default;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(const Window&&) = delete;
	Window& operator=(const Window&&) = delete;

private:

	WindowSpecification m_Spec;

	void* m_ImplPointer = nullptr;

};

