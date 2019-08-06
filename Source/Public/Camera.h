#pragma once

#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>

class Player;

class Camera
{
public:

	Camera(Player* player, glm::vec3 const& position);
	void Translate(glm::vec3 const& translation);
	void Rotate(glm::vec3 const& rotation);
	void Move();	
	void ToggleCameraMode();
	glm::mat4 GenerateViewMatrix() const;

public:

	void SetRotation(glm::vec3 const& rotation);
	void SetPitch(float pitch);
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;

private:

	float CalculateHorizontalDistance() const;
	float CalculateVerticleDistance() const;

private:

	bool m_bFirstPerson = false;
	float m_Distance = 5.f;
	Player* m_Player = nullptr;
	glm::vec3 m_Rotation = glm::vec3(20.f, 180.f, 0); //pitch, yaw, roll
	glm::vec3 m_Position = glm::vec3(0);
};
