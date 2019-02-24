#include "StaticShader.h"

const int StaticShader::MAX_LIGHTS = 4;

StaticShader::StaticShader() : Shader("res/Shaders/Shader.vert", "res/Shaders/Shader.frag")
{
}

void StaticShader::LoadPlane(glm::vec4 plane)
{
	SetVec4("plane", plane);
}

void StaticShader::LoadFakeLighting(bool fake_lighting)
{
	SetBool("fake_lighting", fake_lighting);
}

void StaticShader::LoadLight(std::vector<Light*> lights)
{
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		SetVector("light_position[" + std::to_string(i) + "]", lights[i]->GetPosition());
		SetVector("light_colour[" + std::to_string(i) + "]", lights[i]->GetColour());
		SetVector("attenuation[" + std::to_string(i) + "]", lights[i]->GetAttenuation());
	}
}

void StaticShader::LoadSkyColour(glm::vec3 colour)
{
	SetVector("sky_colour", colour);
}

void StaticShader::LoadViewPosition(glm::vec3 view_position)
{
	SetVector("view_position", view_position);
}

void StaticShader::LoadTransformationMatrix(glm::mat4 transform_matrix)
{
	SetMat4("transform", transform_matrix);
}

void StaticShader::LoadViewMatrix(glm::mat4 view_matrix)
{
	SetMat4("view", view_matrix);
}

void StaticShader::LoadProjectionMatrix(glm::mat4 projection_matrix)
{
	SetMat4("projection", projection_matrix);
}


