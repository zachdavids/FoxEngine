#pragma once

#include <string>

struct GLFWwindow;

class WindowManager
{
public:

	WindowManager();
	void CreateWindow();

public:

	GLFWwindow *GetWindow() const;

private:

	int m_Width;
	int m_Height;
	GLFWwindow* m_Window;
};
