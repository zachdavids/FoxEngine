#include "Player.h"

const float Player::s_RunSpeed = 10.0f;
const float Player::s_TurnSpeed = 1.0f;

Player::Player(Model* model, glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& scale) :
	Entity(model, position, rotation, scale)
{
}

void Player::KeyboardInput(PlayerMovement direction, double delta_time)
{
	if (direction == PlayerMovement::Forward)
	{
		Translate(GetForward() * (float)delta_time * s_RunSpeed);
	}
	if (direction == PlayerMovement::Backward)
	{
		Translate(-GetForward() * (float)delta_time * s_RunSpeed);
	}
	if (direction == PlayerMovement::Left)
	{
		Rotate(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (direction == PlayerMovement::Right)
	{
		Rotate(glm::vec3(0.0f, -1.0f, 0.0f));
	}
	if (direction == PlayerMovement::Up)
	{
		Translate(glm::vec3(0.0f, 0.1f * (float)delta_time * s_RunSpeed, 0.0f));
	}
	if (direction == PlayerMovement::Down)
	{
		Translate(glm::vec3(0.0f, -0.1f * (float)delta_time * s_RunSpeed, 0.0f));
	}
}

void Player::MouseInput(float x_offset, float y_offset, double delta_time)
{
	//TODO UPDATE TO ROTATE AROUND NEW AXIS
	//Rotate(y_offset  * delta_time * TURN_SPEED, 0, 0);
	//Rotate(y_offset  * delta_time * TURN_SPEED, 0, 0);
}
