#pragma once

class Model;

class Skybox
{
public:

	Skybox();
	void Rotate();
	Model* CreateSkybox() const;

public:

	float GetRotation() const;
	Model* GetModel() const;

private:

	float m_Rotation = 0.f;;
	const static float s_Size;
	const static float s_RotateSpeed;
	Model* m_Model;
};
