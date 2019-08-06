#pragma once

#include "Mesh.h"
#include "Texture.h"

#include <assimp/scene.h>

#include <vector>

class Model
{
public:

	Model(Mesh* mesh);
	Model(std::string const& path);
	void LoadModel(std::string const& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterial(aiMaterial* mat, aiTextureType type, std::string const& type_name);

public:

	std::vector<Mesh>& GetMeshes();

private:

	glm::vec3 m_Min;
	glm::vec3 m_Max;
	glm::vec3 m_Size;
	std::string m_Directory;
	std::vector<Mesh> m_Meshes;
	std::vector<Texture> m_LoadedTextures;
};