#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : vertices_(vertices), indices_(indices), textures_(textures)
{
	SetupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures) : vertices_(vertices), textures_(textures)
{
	SetupNonEBOMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices) : vertices_(vertices)
{
	SetupNonEBOMesh();
}

GLuint Mesh::GetVAO()
{
	return VAO_;
}

int Mesh::GetSize()
{
	return indices_.size();
}

int Mesh::GetVerticesCount()
{
	return vertices_.size();
}

std::vector<Texture>& Mesh::GetTextures()
{
	return textures_;
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
	glGenVertexArrays(1, &VAO_);
	glBindVertexArray(VAO_);
}

void Mesh::CreateEBO()
{
	glGenBuffers(1, &EBO_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);
}

void Mesh::CreateVBO()
{
	glGenBuffers(1, &VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_STATIC_DRAW);
}

void Mesh::EnableAttributes()
{
	//Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	//Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal_));
	//Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_uv_));
	//Tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent_));
	//Bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent_));
}

void Mesh::UnbindVAO()
{
	glBindVertexArray(0);
}