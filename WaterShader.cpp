#include "WaterShader.h"

WaterShader::WaterShader() : Shader("res/Shaders/Water.vert", "res/Shaders/Water.frag")
{
}

void WaterShader::LoadTextures()
{
	SetInt("reflection", 0);
	SetInt("refraction", 1);
	SetInt("dudv", 2);
}

void WaterShader::LoadMoveFactor(float move_factor)
{
	SetFloat("move_factor", move_factor);
}

void WaterShader::LoadTransformationMatrix(glm::mat4 transform_matrix)
{
	SetMat4("transform", transform_matrix);
}

void WaterShader::LoadViewMatrix(glm::mat4 view_matrix)
{
	SetMat4("view", view_matrix);
}

void WaterShader::LoadProjectionMatrix(glm::mat4 projection_matrix)
{
	SetMat4("projection", projection_matrix);
}
