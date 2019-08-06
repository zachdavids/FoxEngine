#pragma once

#include <GLM/mat4x4.hpp>

#include <vector>

class Mesh;
class Water;
class WaterShader;
class Framebuffer;

class WaterRenderer
{
public:

	WaterRenderer(WaterShader* shader, Framebuffer* buffer, glm::mat4 const& projection);
	void InitializeModel(Mesh* mesh) const;
	void UnbindModel() const;
	void Render(std::vector<Water*> const& water);
	void LoadModelMatrix(Water* water) const;

private:

	float m_MoveFactor = 0.0f;
	const static float s_WaveSpeed;
	WaterShader* m_Shader = nullptr;
	Framebuffer* m_Framebuffer = nullptr;
	glm::mat4 m_Projection;
};