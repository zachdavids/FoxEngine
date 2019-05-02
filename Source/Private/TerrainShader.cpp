#include "TerrainShader.h"

const int TerrainShader::MAX_LIGHTS = 4;

TerrainShader::TerrainShader() : Shader("Resources/Shaders/Terrain.vert", "Resources/Shaders/Terrain.frag")
{
}

void TerrainShader::LoadPlane(glm::vec4 plane)
{
	SetVec4("plane", plane);
}

void TerrainShader::LoadTextures()
{
	SetInt("background", 0);
	SetInt("r", 1);
	SetInt("g", 2);
	SetInt("b", 3);
	SetInt("blend_map", 4);
}

void TerrainShader::LoadLight(std::vector<Light*> lights)
{
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		SetVector("light_position[" + std::to_string(i) + "]", lights[i]->GetPosition());
		SetVector("light_colour[" + std::to_string(i) + "]", lights[i]->GetColour());
		SetVector("attenuation[" + std::to_string(i) + "]", lights[i]->GetAttenuation());
	}
}

void TerrainShader::LoadSkyColour(glm::vec3 colour)
{
	SetVector("sky_colour", colour);
}

void TerrainShader::LoadViewPosition(glm::vec3 view_position)
{
	SetVector("view_position", view_position);
}

void TerrainShader::LoadTransformationMatrix(glm::mat4 transform_matrix)
{
	SetMat4("transform", transform_matrix);
}

void TerrainShader::LoadViewMatrix(glm::mat4 view_matrix)
{
	SetMat4("view", view_matrix);
}

void TerrainShader::LoadProjectionMatrix(glm::mat4 projection_matrix)
{
	SetMat4("projection", projection_matrix);
}
