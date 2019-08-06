#include "Model.h"
#include "Tools.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>

#include <assimp/postprocess.h>
#include <vector>
#include <iostream>

#include "Tools.h"
#include "Mesh.h"

Model::Model(Mesh* mesh)
{
	m_Meshes.push_back(*mesh);
	m_Max = glm::vec3(0.0f);
	m_Min = glm::vec3(0.0f);
	m_Size = glm::vec3(0.0f);
}

Model::Model(std::string const& path)
{
	m_Max = glm::vec3(0.0f);
	m_Min = glm::vec3(0.0f);
	m_Size = glm::vec3(0.0f);
	LoadModel(path);
}

void Model::LoadModel(std::string const& path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	m_Directory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}

	m_Size.x = m_Max.x - m_Min.x;
	m_Size.y = m_Max.y - m_Min.y;
	m_Size.z = m_Max.z - m_Min.z;
}

Mesh Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;

		if (vector.x > m_Max.x)
			m_Max.x = vector.x;
		if (vector.y > m_Max.y)
			m_Max.y = vector.y;
		if (vector.z > m_Max.z)
			m_Max.z = vector.z;

		if (vector.x < m_Min.x)
			m_Min.x = vector.x;
		if (vector.y < m_Min.y)
			m_Min.y = vector.y;
		if (vector.z < m_Min.z)
			m_Min.z = vector.z;
		vertex.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.uv = vec;
		}
		else
			vertex.uv = glm::vec2(0.0f, 0.0f);
		// tangent
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.tangent = vector;
		// bitangent
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.bitangent = vector;
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<Texture> diffuseMaps = LoadMaterial(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	std::vector<Texture> specularMaps = LoadMaterial(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	std::vector<Texture> normalMaps = LoadMaterial(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	std::vector<Texture> heightMaps = LoadMaterial(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return Mesh(vertices, indices, textures);
}


std::vector<Texture> Model::LoadMaterial(aiMaterial * mat, aiTextureType type, std::string const& type_name)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < m_LoadedTextures.size(); j++)
		{
			if (strcmp(m_LoadedTextures[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(m_LoadedTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{ 
			std::string path = m_Directory + '/' + str.C_Str();
			Texture texture = Tools::LoadTexture(path, type_name);
			textures.push_back(texture);
			m_LoadedTextures.push_back(texture); 
		}
	}
	return textures;
}

std::vector<Mesh>& Model::GetMeshes()
{
	return m_Meshes;
}