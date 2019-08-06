#pragma once

#include "Shader.h"

class Skybox;

class SkyboxShader : public Shader
{
public:

	SkyboxShader();
	void LoadTextures() const;
	void LoadBlendFactor(float blend_factor) const;
	void LoadFogColor(glm::vec3 const& color) const;
	void LoadViewMatrix(Skybox* skybox, glm::mat4 const& view_matrix) const;
	void LoadProjectionMatrix(glm::mat4 const& projection_matrix) const;
};