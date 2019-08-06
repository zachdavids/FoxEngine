#pragma once

#include <GLM/vec3.hpp>

class Light
{
public:

	Light(glm::vec3 const& position, glm::vec3 const& colour, glm::vec3 const& attenuation);

public:

	glm::vec3 GetPosition() const;
	glm::vec3 GetColour() const;
	glm::vec3 GetAttenuation() const;

private:

	glm::vec3 m_Position = glm::vec3(0);
	glm::vec3 m_Color = glm::vec3(1.0f, 0.0, 0.0f);
	glm::vec3 m_Attenuation = glm::vec3(1.0f, 0.0, 0.0f);
};