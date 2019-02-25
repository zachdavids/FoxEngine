#pragma once

#include "Config.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Framebuffer
{
public:
	Framebuffer();
	unsigned int GetReflectionTexture();
	unsigned int GetRefractionTexture();
	void InitializeRefraction();
	void InitializeReflection();
	void BindRefractionFBO();
	void BindReflectionFBO();
	void UnbindFBO();
	const static int REFLECTION_WIDTH;
	const static int REFLECTION_HEIGHT;
	const static int REFRACTION_WIDTH;
	const static int REFRACTION_HEIGHT;
private:
	unsigned int reflection_fbo_;
	unsigned int reflection_rbo_;
	unsigned int reflection_texture_;
	unsigned int refraction_fbo_;
	unsigned int refraction_depth_texture_;
	unsigned int refraction_texture_;

	unsigned int CreateFramebuffer();
	unsigned int CreateTexture(int width, int height);
	unsigned int CreateRenderbuffer(int width, int height);
	unsigned int CreateDepthTexture(int width, int height);

};