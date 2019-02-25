#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Player* player, Model* model, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale, float hp, float tracking_range, float runaway_hp) : Entity(model, position, roll, pitch, yaw, scale), player_(player), hp_(hp), tracking_range_(tracking_range), runaway_hp_(runaway_hp)
{
	fsm_ = new FSM();
	fsm_->PushState(std::bind(&Enemy::Patrol, this));
}

void Enemy::SetSpeed(float speed)
{
	speed_ = speed;
}

float Enemy::GetSpeed()
{
	return speed_;
}

void Enemy::AddWeapon(Weapon::WEAPON_TYPE type)
{
	if (type == Weapon::GATLING)
	{
	}
	else if (type == Weapon::LASER)
	{
		//Model* rocket = new Model("Res/Models/Fighter/Fighter.obj");
		//weapon_ = new Rocket(rocket, GetPosition(), GetRoll(), GetPitch(), GetYaw(), glm::vec3(0.25, 0.25, 0.25));
	}
	else if (type == Weapon::ROCKET)
	{
		Model* rocket = new Model("Res/Models/Rocket/Rocket.obj");
		weapon_ = new Rocket(rocket, GetPosition(), GetRoll(), GetPitch(), GetYaw(), glm::vec3(0.25, 0.25, 0.25));
	}
}

void Enemy::Patrol()
{
	SetForward(player_->GetPosition() - GetPosition());
	float distance = glm::distance(player_->GetPosition(), GetPosition());

	if (distance <= tracking_range_)
	{
		fsm_->PopState();
		fsm_->PushState(std::bind(&Enemy::TrackPlayer, this));
	}
}

void Enemy::TrackPlayer()
{
	SetForward(player_->GetPosition() - GetPosition());
	float distance = glm::distance(player_->GetPosition(), GetPosition());
	if (distance <= weapon_->GetRange())
	{
		fsm_->PopState();
		fsm_->PushState(std::bind(&Enemy::AttackPlayer, this));
	}
	if (distance > tracking_range_)
	{
		fsm_->PopState();
		fsm_->PushState(std::bind(&Enemy::Patrol, this));
	}
}

void Enemy::AttackPlayer()
{
	FireWeapon(GetPosition(), GetForward());
	float distance = glm::distance(player_->GetPosition(), GetPosition());
	std::cout << weapon_->GetRange() << std::endl;
	if (hp_ <= runaway_hp_)
	{
		fsm_->PopState();
		fsm_->PushState(std::bind(&Enemy::RunAway, this));
	}
	if (distance > weapon_->GetRange())
	{
		fsm_->PopState();
		fsm_->PushState(std::bind(&Enemy::TrackPlayer, this));
	}
}

void Enemy::RunAway()
{
	SetForward(-(player_->GetPosition() - GetPosition()));
}

void Enemy::Update(double delta_time)
{
	fsm_->Update();
	Move(delta_time);
}

void Enemy::Move(double delta_time)
{

	if (GetPosition().x <= 0.0f)
	{
		SetPosition(glm::vec3(0.1f, GetPosition().y, GetPosition().z));
		SetForward(-GetForward());
	}
	if (GetPosition().x >= 800.0f)
	{
		SetPosition(glm::vec3(799.0f, GetPosition().y, GetPosition().z));
		SetForward(-GetForward());
	}
	if (GetPosition().z <= 0.0f)
	{
		SetPosition(glm::vec3(GetPosition().x, GetPosition().y, 0.1f));
		SetForward(-GetForward());
	}
	if (GetPosition().z >= 800.0f)
	{
		SetPosition(glm::vec3(GetPosition().x, GetPosition().y, 799.0f));
		SetForward(-GetForward());
	}
	Translate(GetForward() * (float)delta_time * speed_);
}

float Enemy::GetHP()
{
	return hp_;
}

void Enemy::TakeDamage(float damage)
{
	hp_ -= damage;
}
