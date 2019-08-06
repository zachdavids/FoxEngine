#pragma once

#include <GLM/mat4x4.hpp>

class Mesh;
class Skybox;
class SkyboxShader;

class SkyboxRenderer
{
public:

	SkyboxRenderer(SkyboxShader* shader, glm::mat4 const& projection);
	void InitializeModel(Mesh* mesh) const;
	void UnbindModel() const;
	void Render(Skybox* skybox) const;

private:

	float m_BlendFactor = 0.5f;;
	double m_Time = 0.f;
	SkyboxShader* m_Shader;
	glm::mat4 m_Projection;
};