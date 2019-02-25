#pragma once

#include "Shader.h"
#include "Skybox.h"

class SkyboxShader : public Shader
{
public:
	SkyboxShader();
	void LoadTextures();
	void LoadBlendFactor(float blend_factor);
	void LoadFogColor(glm::vec3 color);
	void LoadViewMatrix(Skybox* skybox, glm::mat4 view_matrix);
	void LoadProjectionMatrix(glm::mat4 projection_matrix);
private:
};