#pragma once

#include "Vertex.h"
#include "Texture.h"

#include <vector>

class Mesh
{
public:

	Mesh(std::vector<Vertex> const& vertices);
	Mesh(std::vector<Vertex> const& vertices, std::vector<Texture> const& textures);
	Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned int> const& indices, std::vector<Texture> const& textures = std::vector<Texture>());

public:

	unsigned int GetVAO() const;
	int GetSize() const;
	int GetVerticesCount() const;
	std::vector<Texture>& GetTextures();

private:

	void SetupMesh();
	void SetupNonEBOMesh();
	void CreateVAO();
	void CreateEBO();
	void CreateVBO();
	void EnableAttributes() const;
	void UnbindVAO() const;

private:

	unsigned int m_VAO;
	unsigned int m_EBO;
	unsigned int m_VBO;
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;
};