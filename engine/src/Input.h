#pragma once

#include <GLFW/glfw3.h>

#include "vec2.h"

using namespace math;

class Input
{
public:
	static void init(GLFWwindow* window);

	static bool isPressed(int keyCode);
	static bool isMouseButtonPressed(int button);
	static Vec2 getMousePosition();

private:
	static Input* s_Instance;
	GLFWwindow* m_Window;
};