#include "Entity.h"

#include <glm/gtx/rotate_vector.hpp>

Entity::Entity(Model* model, glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& scale) :
	m_Model(model),
	m_Position(position), 
	m_Rotation(rotation), 
	m_Scale(scale)
{
}

void Entity::Update(double delta_time)
{
}

void Entity::Translate(glm::vec3 const& translation)
{
	m_Position += translation;
}

void Entity::Rotate(glm::vec3 const& rotation)
{
	m_Rotation += rotation;
	CalculateForward(rotation);
	CalculateSide(rotation);
	CalculateUp();
}

void Entity::Scale(glm::vec3 const& scale)
{
	m_Scale = scale;
}

void Entity::CalculateForward(glm::vec3 const& difference)
{
	m_Forward = glm::rotate(m_Forward, glm::radians(difference.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_Forward = glm::rotate(m_Forward, glm::radians(difference.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Forward = glm::rotate(m_Forward, glm::radians(difference.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::CalculateSide(glm::vec3 const& difference)
{
	m_Right = glm::rotate(m_Right, glm::radians(difference.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_Right = glm::rotate(m_Right, glm::radians(difference.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Right = glm::rotate(m_Right, glm::radians(difference.x), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::CalculateUp()
{
	m_Up = glm::cross(m_Forward, m_Right);
}


Model* Entity::GetModel() const
{
	return m_Model;
}

glm::vec3 Entity::GetRotation() const
{
	return m_Rotation;
}

glm::vec3 Entity::GetScale() const
{
	return m_Scale;
}

glm::vec3 Entity::GetPosition() const
{
	return m_Position;
}

glm::vec3 Entity::GetForward() const
{
	return m_Forward;
}

glm::vec3 Entity::GetSide() const
{
	return m_Right;
}

glm::vec3 Entity::GetUp() const
{
	return m_Up;
}

void Entity::SetForward(glm::vec3 const& forward)
{
	m_Forward = forward;
}

void Entity::SetPosition(glm::vec3 const& position)
{
	m_Position = position;
}
