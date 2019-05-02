#include "Entity.h"

Entity::Entity()
{
	hp_ = 100.0f;
}

Entity::Entity(Model* model, glm::vec3 position, float roll, float pitch, float yaw, glm::vec3 scale) : model_(model), position_(position), roll_(roll), pitch_(pitch), yaw_(yaw), scale_(scale)
{
	forward_ = glm::vec3(0.0f, 0.0f, 1.0f);
	//side_ =
	//TODO INIT SIDE
	up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	hp_ = 100.0f;
}

Model* Entity::GetModel()
{
	return model_;
}

void Entity::SetForward(glm::vec3 forward)
{
	forward_ = forward;
}

void Entity::SetPosition(glm::vec3 position)
{
	position_ = position;
}

float Entity::GetRoll()
{
	return roll_;
}

float Entity::GetPitch()
{
	return pitch_;
}

float Entity::GetYaw()
{
	return yaw_;
}

glm::vec3 Entity::GetScale()
{
	return scale_;
}

glm::vec3 Entity::GetPosition()
{
	return position_;
}

glm::vec3 Entity::GetForward()
{
	return forward_;
}

glm::vec3 Entity::GetSide()
{
	return side_;
}

glm::vec3 Entity::GetUp()
{
	return up_;
}

void Entity::Translate(glm::vec3 translation)
{
	position_ += translation;
}

void Entity::Rotate(float pitch, float yaw, float roll)
{
	roll_ += roll;
	pitch_ += pitch;
	yaw_ += yaw;
	CalculateForward(glm::vec3(pitch, yaw, roll));
	CalculateSide(glm::vec3(pitch, yaw, roll));
	CalculateUp();
}

void Entity::Scale(glm::vec3 scale)
{
	scale_ = scale;
}

void Entity::Update(double delta_time)
{

}

void Entity::CalculateForward(glm::vec3 difference)
{
	forward_ = glm::rotate(forward_, glm::radians(difference.x), glm::vec3(1.0f, 0.0f, 0.0f));
	forward_ = glm::rotate(forward_, glm::radians(difference.y), glm::vec3(0.0f, 1.0f, 0.0f));
	forward_ = glm::rotate(forward_, glm::radians(difference.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::CalculateSide(glm::vec3 difference)
{
	side_ = glm::rotate(side_, glm::radians(difference.x), glm::vec3(1.0f, 0.0f, 0.0f));
	side_ = glm::rotate(side_, glm::radians(difference.y), glm::vec3(0.0f, 1.0f, 0.0f));
	side_ = glm::rotate(side_, glm::radians(difference.x), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::CalculateUp()
{
	up_ = glm::cross(forward_, side_);
}
