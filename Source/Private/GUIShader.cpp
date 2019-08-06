#include "GUIShader.h"

GUIShader::GUIShader() : 
	Shader("Resources/Shaders/GUI.vert", "Resources/Shaders/GUI.frag")
{
}

void GUIShader::LoadTransformationMatrix(glm::mat4 const& transform_matrix) const
{
	SetMat4("transform", transform_matrix);
}