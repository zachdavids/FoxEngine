#pragma once

#include "Entity.h"

class Weapon : public Entity
{
public:
	enum WEAPON_TYPE
	{
		GATLING,
		LASER,
		ROCKET,
	};

	Weapon();
	Weapon(Model* model, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale);
	float GetRange();
	float GetSpeed();
	Entity* GetParent();
	glm::vec3 GetDirection();
	void SetRange(float range);
	void SetSpeed(float speed);
private:
	float range_;
	float speed_;
	glm::vec3 direction_;
	Entity* parent_;
};