#include "SkyboxShader.h"
#include "Skybox.h"

#include <GLM/gtc/matrix_transform.hpp>

SkyboxShader::SkyboxShader() : 
	Shader("Resources/Shaders/Skybox.vert", "Resources/Shaders/Skybox.frag")
{
}

void SkyboxShader::LoadTextures() const
{
	SetInt("day_cube", 0);
	SetInt("night_cube", 1);
}

void SkyboxShader::LoadBlendFactor(float blend_factor) const
{
	SetFloat("blend_factor", blend_factor);
}

void SkyboxShader::LoadFogColor(glm::vec3 const& color) const
{
	SetVector("fog_color", color);
}

void SkyboxShader::LoadViewMatrix(Skybox* skybox, glm::mat4 const& view_matrix) const
{
	skybox->Rotate();
	SetMat4("view", glm::rotate(view_matrix, glm::radians(skybox->GetRotation()), glm::vec3(0.0f, 1.0f, 0.0f)));
}

void SkyboxShader::LoadProjectionMatrix(glm::mat4 const& projection_matrix) const
{
	SetMat4("projection", projection_matrix);
}


