#include "WindowManager.h"
#include "Config.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

WindowManager::WindowManager() :
	m_Width(WINDOW_WIDTH),
	m_Height(WINDOW_HEIGHT)
{
	CreateWindow();
}

void WindowManager::CreateWindow()
{
	if (!glfwInit()) 
	{
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, "Starfox", NULL, NULL);
	if (!m_Window) 
	{
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(m_Window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
	}
}

GLFWwindow* WindowManager::GetWindow() const
{
	return m_Window;
}
