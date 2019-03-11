#include "WindowManager.h"
#include "Config.h"

WindowManager::WindowManager()
{
	width_ = WINDOW_WIDTH;;
	height_ = WINDOW_HEIGHT;
	title_ = "Starfox";
	CreateWindow();
}

GLFWwindow * WindowManager::GetWindow()
{
	return window_;
}

void WindowManager::CreateWindow()
{
	// Initialize the window management library (GLFW)
	if (!glfwInit()) {
	}

	// Create a window and its OpenGL context
	window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
	if (!window_) {
		glfwTerminate();
	}

	glfwMakeContextCurrent(window_);
	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Make the window's context the current one
	glfwMakeContextCurrent(window_);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
	}
}
