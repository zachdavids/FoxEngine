#pragma once

class Model;

class Water
{
public:

	Water(float x, float z, float height);
	Model* CreateWater();

public:

	float GetX() const;
	float GetZ() const;
	float GetHeight() const;
	Model* GetModel() const;

public:

	const static float s_TileSize;

private:

	float m_X;
	float m_Z;
	float m_Height;
	Model* m_Model;
};