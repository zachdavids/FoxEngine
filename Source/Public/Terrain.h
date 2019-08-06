#pragma once

#include <stb_image.h>
#include <GLM/vec3.hpp>

#include <vector>

class Model;

class Terrain
{
public:

	Terrain(int grid_x, int grid_y);

public:

	float GetX() const;
	float GetZ() const;
	float GetHeight(float world_x, float world_z) const;
	Model* GetModel() const;

private:

	Model* GenerateTerrain(std::string const& path);
	float CalculateHeight(int x, int z, int width, int height, stbi_uc* image_data) const;
	glm::vec3 CalculateNormal(int x, int z, int width, int height, stbi_uc* image_data) const;

private:

	int m_VertexCount;
	float m_X;
	float m_Z;
	static const int s_Size;
	static const float s_MaxHeight;
	static const float s_MaxPixelColor;
	Model* m_Model;
	std::vector<std::vector<float>> m_Heights;
};