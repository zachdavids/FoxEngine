#pragma once

#include <glm/common.hpp>

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation = glm::vec3(1.0f, 0.0, 0.0f));
	glm::vec3 GetPosition();
	glm::vec3 GetColour();
	glm::vec3 GetAttenuation();
private:
	glm::vec3 position_;
	glm::vec3 colour_;
	glm::vec3 attenuation_;
};