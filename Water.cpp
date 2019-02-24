#include "Water.h"

const float Water::TILE_SIZE = 100.0f;

Water::Water(float x, float z, float height) : x_(x), z_(z), height_(height)
{
	model_ = CreateWater();
}

Model* Water::CreateWater()
{
	 float vertices_array[] = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };

	 std::vector<Vertex> vertices;
	 for (int i = 0; i < sizeof(vertices_array) / sizeof(float); i += 2)
	 {
		 Vertex vertex;
		 glm::vec3 vector;
		 glm::vec2 uv = glm::vec2(1.0f);
		 vector.x = vertices_array[i];
		 vector.y = 0.0f;
		 vector.z = vertices_array[i + 1];
		 vertex.position_ = vector;
		 vector = glm::vec3(1.0f);
		 vertex.texture_uv_ = uv;
		 vertex.normal_ = vector;
		 vertex.tangent_ = vector;
		 vertex.bitangent_ = vector;
		 vertices.push_back(vertex);
	 }
	 std::vector<Texture> textures;
	 Texture dudv = Tools::LoadTexture("Res/Textures/dudv.png");
	 textures.push_back(dudv);

	 return new Model(new Mesh(vertices, textures));
}

float Water::GetX()
{
	return x_;
}

float Water::GetZ()
{
	return z_;
}

float Water::GetHeight()
{
	return height_;
}

Model * Water::GetModel()
{
	return model_;
}
