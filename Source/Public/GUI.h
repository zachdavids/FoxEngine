#pragma once

#include "Texture.h"

#include <GLM/vec3.hpp>

class Model;

class GUI
{
public:

	GUI(glm::vec3 const& position, glm::vec3 const& scale, unsigned int texture);
	void CreateGUI();

public:

	glm::vec3 GetPosition() const;
	glm::vec3 GetScale() const;
	Model* GetModel() const;
	Texture GetTexture() const;

private:

	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	Model* m_Model;
	Texture m_Texture;
};
