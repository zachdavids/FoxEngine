#include "WaterShader.h"

WaterShader::WaterShader() : 
	Shader("Resources/Shaders/Water.vert", "Resources/Shaders/Water.frag")
{
}

void WaterShader::LoadTextures() const
{
	SetInt("reflection", 0);
	SetInt("refraction", 1);
	SetInt("dudv", 2);
}

void WaterShader::LoadMoveFactor(float move_factor) const
{
	SetFloat("move_factor", move_factor);
}

void WaterShader::LoadTransformationMatrix(glm::mat4 const& transform_matrix) const
{
	SetMat4("transform", transform_matrix);
}

void WaterShader::LoadViewMatrix(glm::mat4 const& view_matrix) const
{
	SetMat4("view", view_matrix);
}

void WaterShader::LoadProjectionMatrix(glm::mat4 const& projection_matrix) const
{
	SetMat4("projection", projection_matrix);
}
