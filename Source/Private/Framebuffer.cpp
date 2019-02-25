#include "Framebuffer.h"

const int Framebuffer::REFLECTION_WIDTH = 320;
const int Framebuffer::REFLECTION_HEIGHT = 180;
const int Framebuffer::REFRACTION_WIDTH = 1280;
const int Framebuffer::REFRACTION_HEIGHT = 720;

Framebuffer::Framebuffer()
{
	InitializeRefraction();
	InitializeReflection();
}

unsigned int Framebuffer::GetReflectionTexture()
{
	return reflection_texture_;
}

unsigned int Framebuffer::GetRefractionTexture()
{
	return refraction_texture_;
}

void Framebuffer::InitializeRefraction()
{
	refraction_fbo_ = CreateFramebuffer();
	refraction_texture_ = CreateTexture(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	refraction_depth_texture_ = CreateDepthTexture(REFRACTION_WIDTH, REFRACTION_HEIGHT);
	UnbindFBO();
}

void Framebuffer::InitializeReflection()
{
	reflection_fbo_ = CreateFramebuffer();
	reflection_rbo_ = CreateRenderbuffer(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	reflection_texture_ = CreateTexture(REFLECTION_WIDTH, REFLECTION_HEIGHT);
	UnbindFBO();
}

unsigned int Framebuffer::CreateFramebuffer()
{
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return FBO;
}

unsigned int Framebuffer::CreateRenderbuffer(int width, int height)
{
	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);
	return RBO;
}

unsigned int Framebuffer::CreateTexture(int width, int height)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	return texture;
}

unsigned int Framebuffer::CreateDepthTexture(int width, int height)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
	return texture;
}

void Framebuffer::BindRefractionFBO()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, refraction_fbo_);
	glViewport(0, 0, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void Framebuffer::BindReflectionFBO()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, reflection_fbo_);
	glViewport(0, 0, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void Framebuffer::UnbindFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}


