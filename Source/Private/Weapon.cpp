#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::Weapon(Model * model, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale) : Entity(model, position, roll, pitch, yaw, scale)
{
}

float Weapon::GetRange()
{
	return range_;
}

float Weapon::GetSpeed()
{
	return speed_;
}

Entity * Weapon::GetParent()
{
	return parent_;
}

void Weapon::SetRange(float range)
{
	range_ = range;
}

void Weapon::SetSpeed(float speed)
{
	speed_ = speed;
}

glm::vec3 Weapon::GetDirection()
{
	return direction_;
}
