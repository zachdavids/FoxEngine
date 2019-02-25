#pragma once

#include "Weapon.h"

class Rocket : public Weapon
{
public:
	Rocket(Model* model, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale);
	void Update(double delta_time);
private:
	float cooldown_;
	void Move(double delta_time);
};