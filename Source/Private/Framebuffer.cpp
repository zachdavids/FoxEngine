#include "Framebuffer.h"
#include "Config.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const int Framebuffer::s_ReflectionWidth = 320;
const int Framebuffer::s_ReflectionHeight = 180;
const int Framebuffer::s_RefractionWidth = 1280;
const int Framebuffer::s_RefractionHeight = 720;

Framebuffer::Framebuffer()
{
	InitializeRefraction();
	InitializeReflection();
}

unsigned int Framebuffer::GetReflectionTexture()
{
	return m_ReflectionTexture;
}

unsigned int Framebuffer::GetRefractionTexture()
{
	return m_RefractionTexture;
}

void Framebuffer::InitializeRefraction()
{
	m_RefractionFBO = CreateFramebuffer();
	m_RefractionTexture = CreateTexture(s_RefractionWidth, s_RefractionHeight);
	m_RefractionDepthTexture = CreateDepthTexture(s_RefractionWidth, s_RefractionHeight);
	UnbindFBO();
}

void Framebuffer::InitializeReflection()
{
	m_ReflectionFBO = CreateFramebuffer();
	m_ReflectionRBO = CreateRenderbuffer(s_ReflectionWidth, s_ReflectionHeight);
	m_ReflectionTexture = CreateTexture(s_ReflectionWidth, s_ReflectionHeight);
	UnbindFBO();
}

unsigned int Framebuffer::CreateFramebuffer() const
{
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return FBO;
}

unsigned int Framebuffer::CreateRenderbuffer(int width, int height) const
{
	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);
	return RBO;
}

unsigned int Framebuffer::CreateTexture(int width, int height) const
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

unsigned int Framebuffer::CreateDepthTexture(int width, int height) const
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

void Framebuffer::BindRefractionFBO() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_RefractionFBO);
	glViewport(0, 0, s_RefractionWidth, s_RefractionHeight);
}

void Framebuffer::BindReflectionFBO() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ReflectionFBO);
	glViewport(0, 0, s_ReflectionWidth, s_ReflectionHeight);
}

void Framebuffer::UnbindFBO() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}