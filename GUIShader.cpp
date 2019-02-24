#include "GUIShader.h"

GUIShader::GUIShader() : Shader("res/Shaders/GUI.vert", "res/Shaders/GUI.frag")
{
}

void GUIShader::LoadTransformationMatrix(glm::mat4 transform_matrix)
{
	SetMat4("transform", transform_matrix);
}