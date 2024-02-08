#pragma once

#include <iostream>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "events/windowEvents.h"

class Window
{
public:
	enum ScreenMode { NORMAL_SCREEN = false, FULL_SCREEN = true };

	Window() = delete;
	Window(int width, int height);
	Window(Window&) = delete;
	~Window();

	void onFrameEnd();

	GLFWwindow* getWindowPtr() const { return m_Window; }
	bool getShouldClose() const { return glfwWindowShouldClose(m_Window); }
	int getWidth() const { return m_ScreenProps[m_ScreenMode].width; }
	int getHeight() const { return m_ScreenProps[m_ScreenMode].height; }
	float getAspect() const { return float(getWidth()) / float(getHeight()); }

	void enableVSync()
	{
		m_VSyncEnabled = true;
		glfwSwapInterval(1);
	}
	void disableVSync()
	{
		m_VSyncEnabled = false;
		glfwSwapInterval(0);
	}

	void toggleFullScreen()
	{
		if (m_ScreenMode == FULL_SCREEN)
			m_ScreenMode = NORMAL_SCREEN;
		else
			m_ScreenMode = FULL_SCREEN;

		auto& props = m_ScreenProps[m_ScreenMode];
		glfwSetWindowMonitor(m_Window, props.monitor, props.x, props.y, props.width, props.height, props.refreshRate);

		if (m_VSyncEnabled)
			enableVSync();
		else
			disableVSync();
	}

	static void keyCallback(GLFWwindow* windowPtr, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(windowPtr, GLFW_TRUE);

		if (key == GLFW_KEY_F && action == GLFW_PRESS)
		{
			Window* window = s_Instances[windowPtr];
			window->toggleFullScreen();
		}
	}
	static void resizeCallback(GLFWwindow* windowPtr, int width, int height)
	{
		Window* window = s_Instances[windowPtr];
		window->m_ResizeEvent.notify(width, height);

		window->m_ScreenProps[window->m_ScreenMode].width = width;
		window->m_ScreenProps[window->m_ScreenMode].height = height;
	}
	static void moveCallback(GLFWwindow* windowPtr, int x, int y)
	{
		Window* window = s_Instances[windowPtr];

		window->m_ScreenProps[window->m_ScreenMode].x = x;
		window->m_ScreenProps[window->m_ScreenMode].y = y;
	}
	static void mouseMoveCallback(GLFWwindow* windowPtr, double x, double y)
	{
		Window* window = s_Instances[windowPtr];
		window->m_MouseMoveEvent.notify(float(x), float(y));
	}
	static void mousePressCallback(GLFWwindow* windowPtr, int button, int action, int mods)
	{
		Window* window = s_Instances[windowPtr];
		window->m_MousePressEvent.notify(button);
	}

	WindowResizeEvent& getResizeEvent() { return m_ResizeEvent; }

private:
	static std::unordered_map<GLFWwindow*, Window*> s_Instances;

	GLFWwindow* m_Window;

	struct WindowProps
	{
		GLFWmonitor* monitor;
		int x, y, width, height, refreshRate;
	};

	WindowProps m_ScreenProps[2]; //normal screen, fullscreen
	bool m_VSyncEnabled;
	ScreenMode m_ScreenMode;

	WindowResizeEvent m_ResizeEvent;
	MouseMoveEvent m_MouseMoveEvent;
	MousePressEvent m_MousePressEvent;
};