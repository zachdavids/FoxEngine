#include "Player.h"

const float Player::RUN_SPEED = 10.0f;
const float Player::TURN_SPEED = 1.0f;

Player::Player(Model* model, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale) : Entity(model, position, roll, pitch, yaw, scale)
{
}

void Player::KeyboardInput(Player_Movement direction, double delta_time, Terrain* terrain)
{
	if (direction == FORWARD)
		Translate(GetForward() * (float)delta_time * RUN_SPEED);
	if (direction == BACKWARD)
		Translate(-GetForward() * (float)delta_time * RUN_SPEED);
	if (direction == LEFT)
		Rotate(0.0f, 1.0f, 0.0f);
	if (direction == RIGHT)
		Rotate(0.0f, -1.0f, 0.0f);
	if (direction == UP)
		Translate(glm::vec3(0.0f, 0.1f * (float)delta_time * RUN_SPEED, 0.0f));
	if (direction == DOWN)
		Translate(glm::vec3(0.0f, -0.1f * (float)delta_time * RUN_SPEED, 0.0f));
}

void Player::MouseInput(float x_offset, float y_offset, double delta_time)
{
	//TODO UPDATE TO ROTATE AROUND NEW AXIS
	//Rotate(y_offset  * delta_time * TURN_SPEED, 0, 0);
	//Rotate(y_offset  * delta_time * TURN_SPEED, 0, 0);
}
