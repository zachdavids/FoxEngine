#include "GUI.h"
#include "Model.h"
#include "Vertex.h"

#include <vector>

GUI::GUI(glm::vec3 const& position, glm::vec3 const& scale, unsigned int texture) :
	m_Position(position),
	m_Scale(scale)
{
	CreateGUI();
	m_Texture.id = texture;
}

void GUI::CreateGUI()
{
	float vertices_array[] = { -1, 1, -1, -1, 1, 1, 1, -1 };

	std::vector<Vertex> vertices;
	for (int i = 0; i < sizeof(vertices_array) / sizeof(float); i += 2)
	{
		Vertex vertex;
		vertex.position.x = vertices_array[i];
		vertex.position.y = vertices_array[i + 1];
		vertex.position.z = 0;
		vertices.push_back(vertex);
	}
	
	m_Model = new Model(new Mesh(vertices));
}

glm::vec3 GUI::GetPosition() const
{
	return m_Position;
}

glm::vec3 GUI::GetScale() const
{
	return m_Scale;
}

Model * GUI::GetModel() const
{
	return m_Model;
}

Texture GUI::GetTexture() const
{
	return m_Texture;
}
