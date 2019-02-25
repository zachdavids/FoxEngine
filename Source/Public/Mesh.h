#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/common.hpp>
#include <vector>

#include "Vertex.h"
#include "Texture.h"

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures = std::vector<Texture>());
	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures);
	Mesh(std::vector<Vertex> vertices);
	GLuint GetVAO();
	int GetSize();
	int GetVerticesCount();
	std::vector<Texture>& GetTextures();
private:
	GLuint VAO_, EBO_, VBO_;
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	std::vector<Texture> textures_;

	void SetupMesh();
	void SetupNonEBOMesh();
	void CreateVAO();
	void CreateEBO();
	void CreateVBO();
	void EnableAttributes();
	void UnbindVAO();
};