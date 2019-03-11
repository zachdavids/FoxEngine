#pragma once

#include <iostream>
#include <exception>
#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class WindowManager
{
public:
	WindowManager();
	GLFWwindow *GetWindow();
private:
	int width_;
	int height_;
	double last_frame_;
	double delta_;
	std::string title_;
	void CreateWindow();
	GLFWwindow *window_;
};
