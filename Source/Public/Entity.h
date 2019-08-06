#pragma once

#include <GLM/vec3.hpp>

class Model;

class Entity
{
public:

	Entity() = default;
	Entity(Model* model, glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& scale);
	virtual void Update(double delta_time);

public:

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	glm::vec3 GetForward() const;
	glm::vec3 GetSide() const;
	glm::vec3 GetUp() const;
	Model* GetModel() const;
	void SetForward(glm::vec3 const& forward);
	void SetPosition(glm::vec3 const& position);
	void Translate(glm::vec3 const& translation);
	void Rotate(glm::vec3 const& rotation);
	void Scale(glm::vec3 const& scale);

private:

	void CalculateForward(glm::vec3 const& difference);
	void CalculateSide(glm::vec3 const& difference);
	void CalculateUp();

private:

	float m_HP = 100.f;
	Model* m_Model = nullptr;
	glm::vec3 m_Position = glm::vec3(0);
	glm::vec3 m_Rotation = glm::vec3(0);
	glm::vec3 m_Scale = glm::vec3(0);
	glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 m_Right = glm::vec3(0);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
};
