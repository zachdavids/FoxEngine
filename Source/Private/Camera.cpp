#include "Camera.h"
#include "Player.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

Camera::Camera(Player* player, glm::vec3 const& position) : 
	m_Player(player), 
	m_Position(position)
{
}

void Camera::Translate(glm::vec3 const& translation)
{
	m_Position += translation;
}

void Camera::Rotate(glm::vec3 const& rotation)
{
	m_Rotation += rotation;
}

void Camera::Move()
{
	const glm::vec3 player_position = m_Player->GetPosition();
	const glm::vec3 player_rotation = m_Player->GetRotation();

	if (m_bFirstPerson == false)
	{
		const float h_distance = CalculateHorizontalDistance();
		m_Position.x = player_position.x - h_distance * glm::sin(glm::radians(player_rotation.y));
		m_Position.y = player_position.y + CalculateVerticleDistance();
		m_Position.z = player_position.z - h_distance * glm::cos(glm::radians(player_rotation.y));
	}
	else
	{
		m_Rotation.x = player_rotation.x;
		m_Rotation.z = player_rotation.z;
		m_Position = player_position;
	}

	m_Rotation.y = 180 - player_rotation.y;
}

glm::mat4 Camera::GenerateViewMatrix() const
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::rotate(view, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::translate(view, -m_Position);
	return view;
}

float Camera::CalculateHorizontalDistance() const
{
	return m_Distance * glm::cos(glm::radians(m_Rotation.x));
}

float Camera::CalculateVerticleDistance() const
{
	return m_Distance * glm::sin(glm::radians(m_Rotation.x));
}

void Camera::ToggleCameraMode()
{
	m_bFirstPerson = !m_bFirstPerson;
}

glm::vec3 Camera::GetPosition() const
{
	return m_Position;
}

glm::vec3 Camera::GetRotation() const
{
	return m_Rotation;
}

void Camera::SetRotation(glm::vec3 const& rotation)
{
	m_Rotation = rotation;
}

void Camera::SetPitch(float pitch)
{
	m_Rotation.x = pitch;
}