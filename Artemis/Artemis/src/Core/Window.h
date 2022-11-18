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

	void* GetImplementationPointer() {
		return m_impl_pointer;
	}

	const WindowSpecification& GetSpec() {
		return m_spec;
	}

	Window() = default;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(const Window&&) = delete;
	Window& operator=(const Window&&) = delete;

private:

	WindowSpecification m_spec;

	void* m_impl_pointer = nullptr;

};

