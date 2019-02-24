#pragma once

#include "Enemy.h"
#include "Rocket.h"

class RocketEnemy : public Enemy
{
public:
	RocketEnemy(Player* player, Model* model, Model* weapon, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale);
	void FireWeapon(glm::vec3 position, glm::vec3 forward);
private:
	int rocket_count_;
	float rocket_cooldown_;
	double last_fire_;
	Model* weapon_;
};