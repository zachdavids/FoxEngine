#include "Camera.h"

Camera::Camera(Player* player, glm::vec3 position) : player_(player), position_(position)
{
	roll_ = 0.0f;
	pitch_ = 20.0f;
	yaw_ = 180.0f;
	distance_ = 5.0f;
	first_person_ = false;
}

float Camera::GetRoll()
{
	return roll_;
}

float Camera::GetPitch()
{
	return pitch_;
}

float Camera::GetYaw()
{
	return yaw_;
}

bool Camera::GetCameraMode()
{
	return first_person_;
}

glm::vec3 Camera::GetPosition()
{
	return position_;
}

void Camera::SetPitch(float pitch)
{
	pitch_ = pitch;
}

void Camera::Translate(glm::vec3 translation)
{
	position_ += translation;
}

void Camera::Rotate(float pitch, float yaw, float roll)
{
	roll_ += roll;
	pitch_ += pitch;
	yaw_ += yaw;
}

void Camera::Move()
{
	if (first_person_ == false)
	{
		float horizontal_distance = CalculateHorizontalDistance();
		float verticle_distance = CalculateVerticleDistance();
		CalculatePosition(horizontal_distance, verticle_distance);
		yaw_ = 180 - player_->GetYaw();
	}
	else
	{
		roll_ = player_->GetRoll();
		yaw_ = 180 - player_->GetYaw();
		pitch_ = player_->GetPitch();
		position_ = player_->GetPosition();
	}
}

glm::mat4 Camera::GenerateViewMatrix()
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::rotate(view, glm::radians(pitch_), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(yaw_), glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, glm::radians(roll_), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::translate(view, -position_);
	return view;
}

float Camera::CalculateHorizontalDistance()
{
	return distance_ * glm::cos(glm::radians(pitch_));
}

float Camera::CalculateVerticleDistance()
{
	return distance_ * glm::sin(glm::radians(pitch_));
}

void Camera::CalculatePosition(float horizontal_distance, float verticle_distance)
{
	float x_offset = horizontal_distance * glm::sin(glm::radians(player_->GetYaw()));
	float z_offset = horizontal_distance * glm::cos(glm::radians(player_->GetYaw()));
	position_.x = player_->GetPosition().x - x_offset;
	position_.y = player_->GetPosition().y + verticle_distance;
	position_.z = player_->GetPosition().z - z_offset;
}

void Camera::SetFirstPerson()
{
	if (first_person_ == true)
		first_person_ = false;
	else
		first_person_ = true;
}