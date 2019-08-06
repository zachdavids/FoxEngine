#include "TerrainShader.h"
#include "Light.h"

const int TerrainShader::s_MaxNumberLights = 4;

TerrainShader::TerrainShader() : 
	Shader("Resources/Shaders/Terrain.vert", "Resources/Shaders/Terrain.frag")
{
}

void TerrainShader::LoadPlane(glm::vec4 const& plane) const
{
	SetVec4("plane", plane);
}

void TerrainShader::LoadTextures() const
{
	SetInt("background", 0);
	SetInt("r", 1);
	SetInt("g", 2);
	SetInt("b", 3);
	SetInt("blend_map", 4);
}

void TerrainShader::LoadLight(std::vector<Light*> const& lights) const
{
	for (int i = 0; i < s_MaxNumberLights; i++)
	{
		SetVector("light_position[" + std::to_string(i) + "]", lights[i]->GetPosition());
		SetVector("light_colour[" + std::to_string(i) + "]", lights[i]->GetColour());
		SetVector("attenuation[" + std::to_string(i) + "]", lights[i]->GetAttenuation());
	}
}

void TerrainShader::LoadSkyColour(glm::vec3 const& colour) const
{
	SetVector("sky_colour", colour);
}

void TerrainShader::LoadViewPosition(glm::vec3 const& view_position) const
{
	SetVector("view_position", view_position);
}

void TerrainShader::LoadTransformationMatrix(glm::mat4 const& transform_matrix) const
{
	SetMat4("transform", transform_matrix);
}

void TerrainShader::LoadViewMatrix(glm::mat4 const& view_matrix) const
{
	SetMat4("view", view_matrix);
}

void TerrainShader::LoadProjectionMatrix(glm::mat4 const& projection_matrix) const
{
	SetMat4("projection", projection_matrix);
}
