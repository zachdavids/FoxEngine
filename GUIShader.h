#pragma once

#include "Shader.h"

class GUIShader : public Shader
{
public:
	GUIShader();
	void LoadTransformationMatrix(glm::mat4 transform_matrix);
private:
};