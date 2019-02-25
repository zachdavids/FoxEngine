#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <iostream>

#include "Tools.h"
#include "Mesh.h"

class Model
{
public:
	Model(Mesh* mesh);
	Model(std::string path);
	std::vector<Mesh> GetMeshes();
	std::vector<Mesh> GetMeshes() const;
	void LoadModel(std::string path);
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> LoadMaterial(aiMaterial * mat, aiTextureType type, std::string type_name);
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 size;
private:
	std::string directory_;
	std::vector<Mesh> meshes_;
	std::vector<Texture> loaded_textures_;
};