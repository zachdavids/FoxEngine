#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/transform.hpp>

#include "Player.h"

class Camera
{
public:
	enum Camera_Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	Camera(Player* player, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
	float GetRoll();
	float GetPitch();
	float GetYaw();
	bool GetCameraMode();
	glm::vec3 GetPosition();
	void SetPitch(float pitch);
	void Translate(glm::vec3 translation);
	void Rotate(float pitch, float yaw, float roll);
	void Move();	
	void SetFirstPerson();
	glm::mat4 GenerateViewMatrix();
private:
	float roll_;
	float pitch_;
	float yaw_;
	float distance_;
	bool first_person_;
	glm::vec3 position_;
	float CalculateHorizontalDistance();
	float CalculateVerticleDistance();
	void CalculatePosition(float horizontal_distance, float verticle_distance);
	Player* player_;
};
