#include "GUIShader.h"

GUIShader::GUIShader() : Shader("Resources/Shaders/GUI.vert", "Resources/Shaders/GUI.frag")
{
}

void GUIShader::LoadTransformationMatrix(glm::mat4 transform_matrix)
{
	SetMat4("transform", transform_matrix);
}