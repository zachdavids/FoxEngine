#pragma once

#include "Entity.h"
#include "Terrain.h"
#include "Rocket.h"

class Player : public Entity
{
public:
	enum Player_Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	Player(Model* model, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale);
	void KeyboardInput(Player_Movement direction, double delta_time, Terrain* terrain);
	void MouseInput(float x_offset, float y_offset, double delta_time);
private:
	float hp_;
	static const float RUN_SPEED;
	static const float TURN_SPEED;
};