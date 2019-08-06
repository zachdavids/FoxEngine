#include "Light.h"

Light::Light(glm::vec3 const& position, glm::vec3 const& colour, glm::vec3 const& attenuation) :
	m_Position(position), 
	m_Color(colour), 
	m_Attenuation(attenuation)
{
}

glm::vec3 Light::GetPosition() const
{
	return m_Position;
}

glm::vec3 Light::GetColour() const
{
	return m_Color;
}

glm::vec3 Light::GetAttenuation() const
{
	return m_Attenuation;
}
