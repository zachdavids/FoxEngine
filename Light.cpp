#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 colour, glm::vec3 attenuation) : position_(position), colour_(colour), attenuation_(attenuation)
{
	
}

glm::vec3 Light::GetPosition()
{
	return position_;
}

glm::vec3 Light::GetColour()
{
	return colour_;
}

glm::vec3 Light::GetAttenuation()
{
	return attenuation_;
}
