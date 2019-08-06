#include "StaticShader.h"
#include "Light.h"

const int StaticShader::s_MaxNumberLights = 4;

StaticShader::StaticShader() : 
	Shader("Resources/Shaders/Shader.vert", "Resources/Shaders/Shader.frag")
{
}

void StaticShader::LoadPlane(glm::vec4 const& plane) const
{
	SetVec4("plane", plane);
}

void StaticShader::LoadFakeLighting(bool fake_lighting) const
{
	SetBool("fake_lighting", fake_lighting);
}

void StaticShader::LoadLight(std::vector<Light*> const& lights) const
{
	for (int i = 0; i < s_MaxNumberLights; i++)
	{
		SetVector("light_position[" + std::to_string(i) + "]", lights[i]->GetPosition());
		SetVector("light_colour[" + std::to_string(i) + "]", lights[i]->GetColour());
		SetVector("attenuation[" + std::to_string(i) + "]", lights[i]->GetAttenuation());
	}
}

void StaticShader::LoadSkyColour(glm::vec3 const& colour) const
{
	SetVector("sky_colour", colour);
}

void StaticShader::LoadViewPosition(glm::vec3 const& view_position) const
{
	SetVector("view_position", view_position);
}

void StaticShader::LoadTransformationMatrix(glm::mat4 const& transform_matrix) const
{
	SetMat4("transform", transform_matrix);
}

void StaticShader::LoadViewMatrix(glm::mat4 const& view_matrix) const
{
	SetMat4("view", view_matrix);
}

void StaticShader::LoadProjectionMatrix(glm::mat4 const& projection_matrix) const
{
	SetMat4("projection", projection_matrix);
}


