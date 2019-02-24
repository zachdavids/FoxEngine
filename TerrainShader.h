#pragma once

#include "Shader.h"
#include "Light.h"

class TerrainShader : public Shader
{
public:
	TerrainShader();
	void LoadPlane(glm::vec4 plane);
	void LoadTextures();
	void LoadLight(std::vector<Light*> lights);
	void LoadSkyColour(glm::vec3 colour);
	void LoadViewPosition(glm::vec3 view_position);
	void LoadTransformationMatrix(glm::mat4 transform_matrix);
	void LoadViewMatrix(glm::mat4 view_matrix);
	void LoadProjectionMatrix(glm::mat4 transform_matrix);
private:
	const static int MAX_LIGHTS;
};