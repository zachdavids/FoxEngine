#pragma once

#include "Model.h"
#include "Vertex.h"

class Terrain
{
public:
	Terrain(int grid_x, int grid_y);
	float GetX();
	float GetZ();
	float GetHeight(float world_x, float world_z);
	Model* GetModel();
private:
	float x_;
	float z_;
	int vertex_count_;
	static const int SIZE;
	static const float MAX_HEIGHT;
	static const float MAX_PIXEL_COLOUR;
	float CalculateHeight(int x, int z, int width, int height, stbi_uc* image_data);
	glm::vec3 CalculateNormal(int x, int z, int width, int height, stbi_uc* image_data);
	std::vector<std::vector<float>> heights_;
	Model* model_;
	Model* GenerateTerrain(std::string path);
};