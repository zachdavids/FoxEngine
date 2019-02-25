#include "GUI.h"

GUI::GUI(glm::vec3 position, glm::vec3 scale) : position_(position), scale_(scale)
{
	model_ = CreateGUI();
}

GUI::GUI(glm::vec3 position, glm::vec3 scale, unsigned int texture) : position_(position), scale_(scale)
{
	model_ = CreateGUI();
	texture_.id_ = texture;
}

Model* GUI::CreateGUI()
{
	float vertices_array[] = { -1, 1, -1, -1, 1, 1, 1, -1 };
	std::vector<Vertex> vertices;
	for (int i = 0; i < sizeof(vertices_array) / sizeof(float); i += 2)
	{
		Vertex vertex;
		glm::vec3 vector;
		glm::vec2 uv = glm::vec2(1.0f);
		vector.x = vertices_array[i];
		vector.y = vertices_array[i + 1];
		vector.z = 0;
		vertex.position_ = vector;
		vector = glm::vec3(1.0f);
		vertex.texture_uv_ = uv;
		vertex.normal_ = vector;
		vertex.tangent_ = vector;
		vertex.bitangent_ = vector;
		vertices.push_back(vertex);
	}
	
	texture_ = Tools::LoadTexture("Res/Textures/grass.png");
	return new Model(new Mesh(vertices));
}

glm::vec3 GUI::GetPosition()
{
	return position_;
}

glm::vec3 GUI::GetScale()
{
	return scale_;
}

Model * GUI::GetModel()
{
	return model_;
}

Texture GUI::GetTexture()
{
	return texture_;
}
