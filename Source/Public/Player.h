#pragma once

#include "Entity.h"

class Player : public Entity
{
public:

	enum class PlayerMovement
	{
		Forward,
		Backward,
		Left,
		Right,
		Up,
		Down
	};

	Player(Model* model, glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& scale);
	void KeyboardInput(PlayerMovement direction, double delta_time);
	void MouseInput(float x_offset, float y_offset, double delta_time);
private:

	float m_HP;
	static const float s_RunSpeed;
	static const float s_TurnSpeed;
};