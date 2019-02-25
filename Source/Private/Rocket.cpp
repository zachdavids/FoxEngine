#include "Rocket.h"

Rocket::Rocket(Model* model, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale) : Weapon(model, position, roll, pitch, yaw, scale)
{
	SetRange(50.0f);
	SetSpeed(1.0f);
	cooldown_ = 0.1f;
}

void Rocket::Update(double delta_time)
{
	Move(delta_time);
}

void Rocket::Move(double delta_time)
{
	Translate(GetForward() * (float)delta_time * GetSpeed());
}


