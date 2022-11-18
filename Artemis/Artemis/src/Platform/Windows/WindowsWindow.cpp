
#include "Core/Window.h"
#include "Core/Debug_Test.h"

#include <Windows.h>

#include "GLFW/glfw3.h"

void Window::Create(const WindowSpecification& spec) {

	ART_ASSERT(glfwInit() == GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(spec.width, spec.height, spec.title.c_str(), nullptr,  nullptr);

	ART_ASSERT(window);

	glfwMakeContextCurrent(window);

	m_impl_pointer = window;

	m_spec = spec;

}

void Window::Update()
{

	
	glClear(GL_COLOR_BUFFER_BIT);

	
	glfwSwapBuffers((GLFWwindow*)m_impl_pointer);

	
	glfwPollEvents();

}

bool Window::Open()
{
	return !glfwWindowShouldClose((GLFWwindow*)m_impl_pointer);
}

void Window::Terminate()
{

	glfwTerminate();

}

