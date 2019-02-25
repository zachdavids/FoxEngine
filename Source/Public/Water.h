#pragma once

#include "Model.h"

class Water
{
public:
	Water(float x, float z, float height);
	Model* CreateWater();
	float GetX();
	float GetZ();
	float GetHeight();
	Model* GetModel();
	const static float TILE_SIZE;
private:
	float x_;
	float z_;
	float height_;

	Model* model_;
};