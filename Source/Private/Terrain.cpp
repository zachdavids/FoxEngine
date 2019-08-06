#include "Terrain.h"
#include "Tools.h"

#include <stb_image.h>

const int Terrain::SIZE = 800;
const float Terrain::MAX_HEIGHT = 40.0f;
const float Terrain::MAX_PIXEL_COLOUR = 256;

Terrain::Terrain(int grid_x, int grid_z) : x_(grid_x * SIZE), z_(grid_z * SIZE)
{

	model_ = GenerateTerrain("Resources/Textures/heightmap.png");
}

float Terrain::GetX()
{
	return x_;
}

float Terrain::GetZ()
{
	return z_;
}

float Terrain::GetHeight(float world_x, float world_z)
{
	float grid_size = SIZE / static_cast<float>(heights_.size() - 1);
	float terrain_x = world_x - x_;
	float terrain_z = world_z - z_;
	int grid_x = static_cast<int>(floor(terrain_x / grid_size));
	int grid_z = static_cast<int>(floor(terrain_z / grid_size));
	if (grid_x >= heights_.size() - 1 || grid_x < 0 || grid_z >= heights_.size() - 1 || grid_z < 0)
		return 0.0f;
	float x_coord = fmod(terrain_x, grid_size) / grid_size;
	float z_coord = fmod(terrain_z, grid_size) / grid_size;
	float answer;
	if (x_coord <= (1 - z_coord))
	{
		answer = Tools::CalculateBaryCentric(glm::vec2(x_coord, z_coord), 
			glm::vec3(0.0f, heights_[grid_x][grid_z], 0.0f), glm::vec3(1.0f, heights_[grid_x + 1][grid_z], 0.0f), glm::vec3(0.0f, heights_[grid_x][grid_z + 1], 1.0f));
	}
	else
	{
		answer = Tools::CalculateBaryCentric(glm::vec2(x_coord, z_coord), 
			glm::vec3(1.0f, heights_[grid_x + 1][grid_z], 0.0f), glm::vec3(1.0f, heights_[grid_x + 1][grid_z + 1], 1.0f), glm::vec3(0.0f, heights_[grid_x][grid_z + 1], 1.0f));
	}
	return answer;
}

Model * Terrain::GetModel()
{
	return model_;
}

float Terrain::CalculateHeight(int x, int z, int width, int height, stbi_uc* image_data)
{
	if (x < 0 || x >= height || z < 0 || z >= height)
		return 0.0f;
	float pixel = image_data[width * z + x];
	pixel -= MAX_PIXEL_COLOUR / 2.0f;
	pixel /= MAX_PIXEL_COLOUR / 2.0f;
	pixel *= MAX_HEIGHT;
	return pixel;
}

glm::vec3 Terrain::CalculateNormal(int x, int z, int width, int height, stbi_uc* image_data)
{
	float left_pixel = CalculateHeight(x - 1, z, width, height, image_data);
	float right_pixel = CalculateHeight(x + 1, z, width, height, image_data);
	float top_pixel = CalculateHeight(x, z - 1, width, height, image_data);
	float bottom_pixel = CalculateHeight(x, z + 1, width, height, image_data);

	glm::vec3 normal = glm::normalize(glm::vec3(left_pixel - right_pixel, 2.0f, bottom_pixel - top_pixel));
	return normal;
}

Model* Terrain::GenerateTerrain(std::string path)
{
	int width, height, components;
	stbi_uc* image_data = stbi_load(path.c_str(), &width, &height, &components, 1);
	vertex_count_ = height;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (int i = 0; i < vertex_count_; i++)
	{
		std::vector<float> temp;
		heights_.push_back(temp);
	}

	float vertex_height;
	for (int i = 0; i < vertex_count_; i++) {
		for (int j = 0; j < vertex_count_; j++) {	
			Vertex vertex;
			glm::vec3 vector;
			vector.x = static_cast<float>(j) / (static_cast<float>(vertex_count_) - 1) * SIZE;
			vertex_height = CalculateHeight(j, i, width, height, image_data);
			vector.y = vertex_height;
			vector.z = static_cast<float>(i) / (static_cast<float>(vertex_count_) - 1) * SIZE;
			vertex.position = vector;
			vertex.normal = CalculateNormal(j, i, width, height, image_data);
			vertex.tangent = vector;
			vertex.bitangent = vector;
			glm::vec2 uv;
			uv.x = static_cast<float>(j) / (static_cast<float>(vertex_count_) - 1);
			uv.y = static_cast<float>(i) / (static_cast<float>(vertex_count_) - 1);
			vertex.uv = uv;
			vertices.push_back(vertex);
			heights_[j].push_back(vertex_height);
		}
	}

	for (int gz = 0; gz < vertex_count_ - 1; gz++) {
		for (int gx = 0; gx < vertex_count_ - 1; gx++) {
			int top_left = (gz * vertex_count_) + gx;
			int top_right = top_left + 1;
			int bottom_left = ((gz + 1) * vertex_count_) + gx;
			int bottom_right = bottom_left + 1;
			indices.push_back(top_left);
			indices.push_back(bottom_left);
			indices.push_back(top_right);
			indices.push_back(top_right);
			indices.push_back(bottom_left);
			indices.push_back(bottom_right);
		}
	}

	stbi_image_free(image_data);
	std::vector<Texture> test;

	Texture background = Tools::LoadTexture("Resources/Textures/grass.png");
	test.push_back(background);
	Texture r = Tools::LoadTexture("Resources/Textures/dirt.png");
	test.push_back(r);
	Texture g = Tools::LoadTexture("Resources/Textures/flowers.png");
	test.push_back(g);
	Texture b = Tools::LoadTexture("Resources/Textures/path.png");
	test.push_back(b);
	Texture blend_map = Tools::LoadTexture("Resources/Textures/blend.png");
	test.push_back(blend_map);
	return new Model(new Mesh(vertices, indices, test));
}
