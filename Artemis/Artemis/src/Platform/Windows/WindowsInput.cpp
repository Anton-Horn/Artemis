
#include "Core\Input.h"

#include "Core\Log.h"

#include "GLFW\glfw3.h"
#include "Core\Application.h"


float m_ScrollWheelValue;

void ScrollWheelCallback(GLFWwindow*, double xoffset, double yoffset) {
	m_ScrollWheelValue += (float)yoffset;
}

void Input::Init() {
	glfwSetScrollCallback((GLFWwindow*)Application::GetWindow().GetImplementationPointer(), ScrollWheelCallback);
}

bool Input::KeyPressed(KeyCode keycode)
{
	if (glfwGetKey((GLFWwindow*)Application::GetWindow().GetImplementationPointer(), (int)keycode) == GLFW_PRESS) {
		return true;
	}
	return false;
}

bool Input::KeyReleased(KeyCode keycode)
{
	if (glfwGetKey((GLFWwindow*)Application::GetWindow().GetImplementationPointer(), (int)keycode) == GLFW_RELEASE) {
		return true;
	}
	return false;
}

KeyCode last_pressed_key = KeyCode::NONE;

bool Input::KeyClicked(KeyCode keycode)
{

	if (KeyReleased(last_pressed_key))
	{
		last_pressed_key = KeyCode::NONE;
	}

	if (KeyPressed(keycode) && last_pressed_key != keycode)
	{
		last_pressed_key = keycode;
		return true;
	}

	return false;
}

MouseCode last_pressed_mousebutton = MouseCode::NONE;

bool Input::MouseButtonClicked(MouseCode mousecode)
{
	if (MouseButtonReleased(last_pressed_mousebutton))
	{
		last_pressed_mousebutton = MouseCode::NONE;
	}

	if (MouseButtonPressed(mousecode) && last_pressed_mousebutton != mousecode)
	{
		last_pressed_mousebutton = mousecode;
		return true;
	}

	return false;
}


int Input::GetMouseX()
{
	double x = 0;
	double y = 0;
	glfwGetCursorPos((GLFWwindow*)Application::GetWindow().GetImplementationPointer(), &x, &y);
	return (int)x;
}

int Input::GetMouseY()
{
	double x = 0;
	double y = 0;
	glfwGetCursorPos((GLFWwindow*)Application::GetWindow().GetImplementationPointer(), &x, &y);
	return (int)y;
}

bool Input::MouseButtonPressed(MouseCode mousecode)
{
	if (glfwGetMouseButton((GLFWwindow*)Application::GetWindow().GetImplementationPointer(), (int)mousecode) == GLFW_PRESS) return true;
	return false;
}

bool Input::MouseButtonReleased(MouseCode mousecode)
{
	if (glfwGetMouseButton((GLFWwindow*)Application::GetWindow().GetImplementationPointer(), (int)mousecode) == GLFW_RELEASE) return true;
	return false;
}

float Input::GetMouseWheelValue()
{
	return m_ScrollWheelValue;
}

std::string Input::GetKeyName(KeyCode keycode)
{
	return glfwGetKeyName((int)keycode, 0);
}

