#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>

#include "Model.h"

class GUI
{
public:
	GUI(glm::vec3 position, glm::vec3 scale);
	GUI(glm::vec3 position, glm::vec3 scale, unsigned int texture);
	Model* CreateGUI();
	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	Model* GetModel();
	Texture GetTexture();
private:
	glm::vec3 position_;
	glm::vec3 scale_;
	Model* model_;
	Texture texture_;
};
