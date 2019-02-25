#pragma once

#include "Entity.h"
#include "FSM.h"
#include "Player.h"
#include "Weapon.h"
#include "Rocket.h"
#include "Laser.h"
#include "Gatling.h"
#include <time.h>

class Enemy : public Entity
{
public:
	Enemy();
	Enemy(Player* player, Model* model, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale, float hp = 100.0f, float tracking_range = 40.0f, float runaway_hp = 10.0f);
	void SetSpeed(float speed);
	float GetSpeed();
	void AddWeapon(Weapon::WEAPON_TYPE type);
	void Patrol();
	void TrackPlayer();
	void AttackPlayer();
	void RunAway();
	void Update(double delta_time);
	void Move(double delta_time);
	float GetHP();
	void TakeDamage(float damage);
	virtual void FireWeapon(glm::vec3 position, glm::vec3 direction) {};
private:
	float hp_;
	float runaway_hp_;
	float tracking_range_;
	float speed_;
	FSM* fsm_;
	Player* player_;
	Weapon* weapon_;
};