#include "SkyboxShader.h"

SkyboxShader::SkyboxShader() : Shader("Resources/Shaders/Skybox.vert", "Resources/Shaders/Skybox.frag")
{
}

void SkyboxShader::LoadTextures()
{
	SetInt("day_cube", 0);
	SetInt("night_cube", 1);
}

void SkyboxShader::LoadBlendFactor(float blend_factor)
{
	SetFloat("blend_factor", blend_factor);
}

void SkyboxShader::LoadFogColor(glm::vec3 color)
{
	SetVector("fog_color", color);
}

void SkyboxShader::LoadViewMatrix(Skybox* skybox, glm::mat4 view_matrix)
{
	skybox->Rotate();
	SetMat4("view", glm::rotate(view_matrix, glm::radians(skybox->GetRotation()), glm::vec3(0.0f, 1.0f, 0.0f)));
}

void SkyboxShader::LoadProjectionMatrix(glm::mat4 projection_matrix)
{
	SetMat4("projection", projection_matrix);
}


