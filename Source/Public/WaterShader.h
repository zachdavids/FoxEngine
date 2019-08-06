#pragma once

#include "Shader.h"

class WaterShader : public Shader 
{
public:

	WaterShader();
	void LoadTextures() const;
	void LoadMoveFactor(float move_factor) const;
	void LoadTransformationMatrix(glm::mat4 const& transform_matrix) const;
	void LoadViewMatrix(glm::mat4 const& view_matrix) const;
	void LoadProjectionMatrix(glm::mat4 const& projection_matrix) const;
};