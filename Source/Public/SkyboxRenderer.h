#pragma once

#include "SkyboxShader.h"
#include "Skybox.h"
#include "Camera.h"

class SkyboxRenderer
{
public:

	SkyboxRenderer(SkyboxShader* shader, glm::mat4 projection);
	void InitializeModel(Mesh* mesh);
	void UnbindModel();
	void Render(Skybox* skybox);

private:

	float blend_factor_;
	double time_;
	SkyboxShader* shader_;
	glm::mat4 projection_;

};