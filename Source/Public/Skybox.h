#pragma once

#include "Model.h"

class Skybox
{
public:
	Skybox();
	Model* CreateSkybox();
	Model* GetModel();
	float GetRotation();
	void Rotate();
private:
	Model* model_;
	const static float SIZE;
	const static float ROTATE_SPEED;
	float rotation_;
};
