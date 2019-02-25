#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Mesh.h"
#include "Model.h"

class Entity
{
public:
	Entity();
	Entity(Model* model, glm::vec3 position, float pitch, float yaw, float roll, glm::vec3 scale);

	float GetRoll();
	float GetPitch();
	float GetYaw();
	glm::vec3 GetScale();
	glm::vec3 GetPosition();
	glm::vec3 GetForward();
	glm::vec3 GetSide();
	glm::vec3 GetUp();
	Model* GetModel();
	void SetForward(glm::vec3 forward);
	void SetPosition(glm::vec3 position);
	void Translate(glm::vec3 translation);
	void Rotate(float roll, float pitch, float yaw);
	void Scale(glm::vec3 scale);
	virtual void Update(double delta_time) {};
	void AddEntity(Entity* entity);
	std::vector<Entity*> GetSubEntities();
private:
	float hp_;
	float roll_;
	float pitch_;
	float yaw_;
	glm::vec3 position_;
	glm::vec3 scale_;
	glm::vec3 forward_;
	glm::vec3 side_;
	glm::vec3 up_;
	Model* model_;
	void CalculateForward(glm::vec3 difference);
	void CalculateSide(glm::vec3 difference);
	void CalculateUp();
	std::vector<Entity*> sub_entities_;
};
