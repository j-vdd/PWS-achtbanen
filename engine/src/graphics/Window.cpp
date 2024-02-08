#include "Window.h"

#include <iostream>

std::unordered_map<GLFWwindow*, Window*> Window::s_Instances = {};

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

Window::Window(int width, int height)
	: m_VSyncEnabled(false), m_ScreenMode(NORMAL_SCREEN)
{
    if (!glfwInit())
    {
        fprintf(stderr, "Glfw could not init");
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //TODO: don't hardcode
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    m_Window = glfwCreateWindow(width, height, "My game", NULL, NULL);
    if (!m_Window)
    {
        fprintf(stderr, "Glfw could not create a window");
    }
    s_Instances[m_Window] = this;

    glfwMakeContextCurrent(m_Window);
    gladLoadGL();

    int xPos, yPos;
    glfwGetWindowPos(m_Window, &xPos, &yPos);
    m_ScreenProps[ScreenMode::NORMAL_SCREEN] = {
        NULL, xPos, yPos, width, height, 0
    };

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    m_ScreenProps[ScreenMode::FULL_SCREEN] = {
        monitor, 0, 0, mode->width, mode->height, mode->refreshRate
    };

    glfwSetKeyCallback(m_Window, keyCallback);
    glfwSetWindowSizeCallback(m_Window, resizeCallback);
    glfwSetWindowPosCallback(m_Window, moveCallback);
    glfwSetMouseButtonCallback(m_Window, mousePressCallback);
    glfwSetCursorPosCallback(m_Window, mouseMoveCallback);

    //glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE); //TODO: not here

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
Window::~Window() 
{
    glfwDestroyWindow(m_Window);

    glfwTerminate();
}

void Window::onFrameEnd() 
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}