#pragma once

#include "Shader.h"
#include "Light.h"

class StaticShader : public Shader
{
public:
	StaticShader();
	void LoadPlane(glm::vec4 plane);
	void LoadFakeLighting(bool fake_lighting);
	void LoadLight(std::vector<Light*> light);
	void LoadSkyColour(glm::vec3 colour);
	void LoadViewPosition(glm::vec3 view_position);
	void LoadTransformationMatrix(glm::mat4 transform_matrix);
	void LoadViewMatrix(glm::mat4 view_matrix);
	void LoadProjectionMatrix(glm::mat4 transform_matrix);
private:
	const static int MAX_LIGHTS;
};