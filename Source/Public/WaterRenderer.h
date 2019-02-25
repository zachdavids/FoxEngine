#pragma once

#include "Water.h"
#include "WaterShader.h"
#include "Model.h"
#include "Framebuffer.h"

class WaterRenderer
{
public:
	WaterRenderer(WaterShader* shader, Framebuffer* buffer, glm::mat4 projection);
	void InitializeModel(Mesh * mesh);
	void UnbindModel();
	void Render(std::vector<Water*> water);
	void LoadModelMatrix(Water * water);
	const static float WAVE_SPEED;
private:
	bool initialized_;
	float move_factor_;
	WaterShader* shader_;
	Framebuffer* buffer_;
	glm::mat4 projection_;
};