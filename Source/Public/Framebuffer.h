#pragma once

class Framebuffer
{
public:

	Framebuffer();
	void BindRefractionFBO() const;
	void BindReflectionFBO() const;
	void UnbindFBO() const;

public:

	unsigned int GetReflectionTexture();
	unsigned int GetRefractionTexture();

private:

	void InitializeRefraction();
	void InitializeReflection();
	unsigned int CreateFramebuffer() const;
	unsigned int CreateTexture(int width, int height) const;
	unsigned int CreateRenderbuffer(int width, int height) const;
	unsigned int CreateDepthTexture(int width, int height) const;

private:

	unsigned int m_ReflectionFBO;
	unsigned int m_ReflectionRBO;
	unsigned int m_ReflectionTexture;
	unsigned int m_RefractionFBO;
	unsigned int m_RefractionDepthTexture;
	unsigned int m_RefractionTexture;
	const static int s_ReflectionWidth;
	const static int s_ReflectionHeight;
	const static int s_RefractionWidth;
	const static int s_RefractionHeight;
};