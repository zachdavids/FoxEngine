#include "Mesh.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/common.hpp>

#include <vector>

Mesh::Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned int> const& indices, std::vector<Texture> const& textures) : 
	m_Vertices(vertices),
	m_Indices(indices),
	m_Textures(textures)
{
	SetupMesh();
}

Mesh::Mesh(std::vector<Vertex> const& vertices, std::vector<Texture> const& textures) : 
	m_Vertices(vertices),
	m_Textures(textures)
{
	SetupNonEBOMesh();
}

Mesh::Mesh(std::vector<Vertex> const& vertices) : 
	m_Vertices(vertices)
{
	SetupNonEBOMesh();
}

unsigned int Mesh::GetVAO() const
{
	return m_VAO;
}

int Mesh::GetSize() const
{
	return m_Indices.size();
}

int Mesh::GetVerticesCount() const
{
	return m_Vertices.size();
}

std::vector<Texture>& Mesh::GetTextures()
{
	return m_Textures;
}

void Mesh::SetupMesh()
{
	CreateVAO();
	CreateEBO();
	CreateVBO();
	EnableAttributes();
	UnbindVAO();
}

void Mesh::SetupNonEBOMesh()
{
	CreateVAO();
	CreateVBO();
	EnableAttributes();
	UnbindVAO();
}

void Mesh::CreateVAO()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
}

void Mesh::CreateEBO()
{
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);
}

void Mesh::CreateVBO()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);
}

void Mesh::EnableAttributes() const
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
}

void Mesh::UnbindVAO() const
{
	glBindVertexArray(0);
}