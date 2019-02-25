#include "RocketEnemy.h"

RocketEnemy::RocketEnemy(Player* player, Model* model, Model* weapon, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale) : Enemy(player, model, position, roll, pitch, yaw, scale), weapon_(weapon)
{
	SetSpeed(0.25f);
	AddWeapon(Weapon::ROCKET);
	rocket_cooldown_ = 4.0f;
	last_fire_ = 0.0f;
}

void RocketEnemy::FireWeapon(glm::vec3 position, glm::vec3 forward)
{
	if (glfwGetTime() - last_fire_ > rocket_cooldown_)
	{
		Rocket* rocket = new Rocket(weapon_, position, 90, 0, 0, glm::vec3(1.0f, 1.0f, 1.0f));
		rocket->SetForward(forward);
		AddEntity(rocket);
		last_fire_ = glfwGetTime();
	}
}