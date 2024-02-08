#include "Input.h"

Input* Input::s_Instance = nullptr;

void Input::init(GLFWwindow* window)
{
	s_Instance = new Input();
	s_Instance->m_Window = window;
}

bool Input::isPressed(int keycode)
{
	auto window = s_Instance->m_Window;
	auto state = glfwGetKey(window, keycode);

	return state == GLFW_PRESS || state == GLFW_REPEAT;
}
bool Input::isMouseButtonPressed(int button)
{
	auto window = s_Instance->m_Window;
	auto state = glfwGetMouseButton(window, button);

	return state == GLFW_PRESS;
}
Vec2 Input::getMousePosition()
{
	auto window = s_Instance->m_Window;
	double posX, posY;
	glfwGetCursorPos(window, &posX, &posY);

	return { (float)posX, (float)posY };
}