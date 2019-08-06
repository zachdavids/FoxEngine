#include "Water.h"
#include "Model.h"
#include "Vertex.h"
#include "Tools.h"

#include <vector>

const float Water::s_TileSize = 100.0f;

Water::Water(float x, float z, float height) : 
	m_X(x), 
	m_Z(z), 
	m_Height(height)
{
	m_Model = CreateWater();
}

Model* Water::CreateWater()
{
	 float vertices_array[] = { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };

	 std::vector<Vertex> vertices;
	 for (int i = 0; i < sizeof(vertices_array) / sizeof(float); i += 2)
	 {
		 Vertex vertex;
		 vertex.position.x = vertices_array[i];
		 vertex.position.y = 0.0f;
		 vertex.position.z = vertices_array[i + 1];
		 vertices.push_back(vertex);
	 }

	 std::vector<Texture> textures;
	 Texture dudv = Tools::LoadTexture("Resources/Textures/dudv.png");
	 textures.push_back(dudv);

	 return new Model(new Mesh(vertices, textures));
}

float Water::GetX() const
{
	return m_X;
}

float Water::GetZ() const
{
	return m_Z;
}

float Water::GetHeight() const
{
	return m_Height;
}

Model * Water::GetModel() const
{
	return m_Model;
}
