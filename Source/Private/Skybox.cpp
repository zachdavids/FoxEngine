#include "Skybox.h"
#include "Tools.h"
#include "Model.h"
#include "Vertex.h"

const float Skybox::s_Size = 500.0f;
const float Skybox::s_RotateSpeed = 0.001f;

Skybox::Skybox()
{
	m_Model = CreateSkybox();
}

Model* Skybox::CreateSkybox() const
{
	float vertices_array[] = {
		-s_Size,-s_Size,-s_Size, // triangle 1 : begin
		-s_Size,-s_Size, s_Size,
		-s_Size, s_Size, s_Size, // triangle 1 : end
		s_Size, s_Size,-s_Size, // triangle 2 : begin
		-s_Size,-s_Size,-s_Size,
		-s_Size, s_Size,-s_Size, // triangle 2 : end
		s_Size,-s_Size, s_Size,
		-s_Size,-s_Size,-s_Size,
		s_Size,-s_Size,-s_Size,
		s_Size, s_Size,-s_Size,
		s_Size,-s_Size,-s_Size,
		-s_Size,-s_Size,-s_Size,
		-s_Size,-s_Size,-s_Size,
		-s_Size, s_Size, s_Size,
		-s_Size, s_Size,-s_Size,
		s_Size,-s_Size, s_Size,
		-s_Size,-s_Size, s_Size,
		-s_Size,-s_Size,-s_Size,
		-s_Size, s_Size, s_Size,
		-s_Size,-s_Size, s_Size,
		s_Size,-s_Size, s_Size,
		s_Size, s_Size, s_Size,
		s_Size,-s_Size,-s_Size,
		s_Size, s_Size,-s_Size,
		s_Size,-s_Size,-s_Size,
		s_Size, s_Size, s_Size,
		s_Size,-s_Size, s_Size,
		s_Size, s_Size, s_Size,
		s_Size, s_Size,-s_Size,
		-s_Size, s_Size,-s_Size,
		s_Size, s_Size, s_Size,
		-s_Size, s_Size,-s_Size,
		-s_Size, s_Size, s_Size,
		s_Size, s_Size, s_Size,
		-s_Size, s_Size, s_Size,
		s_Size,-s_Size, s_Size
	};


	std::vector<Vertex> vertices;
	for (int i = 0; i < sizeof(vertices_array) / sizeof(float); i += 3) 
	{
		Vertex vertex;
		vertex.position.x = -vertices_array[i];
		vertex.position.y = -vertices_array[i + 1];
		vertex.position.z = -vertices_array[i + 2];
		vertices.push_back(vertex);
	}

	std::vector<Texture> textures;

	std::vector<std::string> paths;
	std::string right = "Resources/Textures/right.png";
	paths.push_back(right);
	std::string left = "Resources/Textures/left.png";
	paths.push_back(left);
	std::string top = "Resources/Textures/top.png";
	paths.push_back(top);
	std::string bottom = "Resources/Textures/bottom.png";
	paths.push_back(bottom);
	std::string back = "Resources/Textures/back.png";
	paths.push_back(back);
	std::string front = "Resources/Textures/front.png";
	paths.push_back(front);
	Texture day_cube = Tools::LoadCubeTexture(paths);
	textures.push_back(day_cube);

	paths.clear();
	right = "Resources/Textures/nightRight.png";
	paths.push_back(right);
	left = "Resources/Textures/nightLeft.png";
	paths.push_back(left);
	top = "Resources/Textures/nightTop.png";
	paths.push_back(top);
	bottom = "Resources/Textures/nightBottom.png";
	paths.push_back(bottom);
	back = "Resources/Textures/nightBack.png";
	paths.push_back(back);
	front = "Resources/Textures/nightFront.png";
	paths.push_back(front);
	Texture night_cube = Tools::LoadCubeTexture(paths);
	textures.push_back(night_cube);

	return new Model(new Mesh(vertices, textures));
}

void Skybox::Rotate()
{
	m_Rotation += s_RotateSpeed;
}


Model* Skybox::GetModel() const
{
	return m_Model;
}

float Skybox::GetRotation() const
{
	return m_Rotation;
}

