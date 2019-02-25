#pragma once

#include "Shader.h"

class WaterShader : public Shader 
{
public:
	WaterShader();
	void LoadTextures();
	void LoadMoveFactor(float move_factor);
	void LoadTransformationMatrix(glm::mat4 transform_matrix);
	void LoadViewMatrix(glm::mat4 view_matrix);
	void LoadProjectionMatrix(glm::mat4 projection_matrix);
private:
};