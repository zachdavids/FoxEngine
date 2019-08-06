#pragma once

#include "Shader.h"

#include <vector>

class Light;

class StaticShader : public Shader
{
public:

	StaticShader();
	void LoadPlane(glm::vec4 const& plane) const;
	void LoadFakeLighting(bool fake_lighting) const;
	void LoadLight(std::vector<Light*> const& light) const;
	void LoadSkyColour(glm::vec3 const& colour) const;
	void LoadViewPosition(glm::vec3 const& view_position) const;
	void LoadTransformationMatrix(glm::mat4 const& transform_matrix) const;
	void LoadViewMatrix(glm::mat4 const& view_matrix) const;
	void LoadProjectionMatrix(glm::mat4 const& transform_matrix) const;

private:

	const static int s_MaxNumberLights;
};