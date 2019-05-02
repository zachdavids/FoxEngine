#include "Skybox.h"

const float Skybox::SIZE = 500.0f;
const float Skybox::ROTATE_SPEED = 0.005f;

Skybox::Skybox()
{
	model_ = CreateSkybox();
	rotation_ = 0.0f;
}

Model* Skybox::CreateSkybox()
{
	float vertices_array[] = {
		-SIZE,-SIZE,-SIZE, // triangle 1 : begin
		-SIZE,-SIZE, SIZE,
		-SIZE, SIZE, SIZE, // triangle 1 : end
		SIZE, SIZE,-SIZE, // triangle 2 : begin
		-SIZE,-SIZE,-SIZE,
		-SIZE, SIZE,-SIZE, // triangle 2 : end
		SIZE,-SIZE, SIZE,
		-SIZE,-SIZE,-SIZE,
		SIZE,-SIZE,-SIZE,
		SIZE, SIZE,-SIZE,
		SIZE,-SIZE,-SIZE,
		-SIZE,-SIZE,-SIZE,
		-SIZE,-SIZE,-SIZE,
		-SIZE, SIZE, SIZE,
		-SIZE, SIZE,-SIZE,
		SIZE,-SIZE, SIZE,
		-SIZE,-SIZE, SIZE,
		-SIZE,-SIZE,-SIZE,
		-SIZE, SIZE, SIZE,
		-SIZE,-SIZE, SIZE,
		SIZE,-SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE,-SIZE,-SIZE,
		SIZE, SIZE,-SIZE,
		SIZE,-SIZE,-SIZE,
		SIZE, SIZE, SIZE,
		SIZE,-SIZE, SIZE,
		SIZE, SIZE, SIZE,
		SIZE, SIZE,-SIZE,
		-SIZE, SIZE,-SIZE,
		SIZE, SIZE, SIZE,
		-SIZE, SIZE,-SIZE,
		-SIZE, SIZE, SIZE,
		SIZE, SIZE, SIZE,
		-SIZE, SIZE, SIZE,
		SIZE,-SIZE, SIZE
	};


	std::vector<Vertex> vertices;
	for (int i = 0; i < sizeof(vertices_array) / sizeof(float); i += 3) 
	{
		Vertex vertex;
		glm::vec3 vector;
		glm::vec2 uv = glm::vec2(1.0f);
		vector.x = -vertices_array[i];
		vector.y = -vertices_array[i + 1];
		vector.z = -vertices_array[i + 2];
		vertex.position_ = vector;
		vector = glm::vec3(1.0f);
		vertex.texture_uv_ = uv;
		vertex.normal_ = vector;
		vertex.tangent_ = vector;
		vertex.bitangent_ = vector;
		vertices.push_back(vertex);
	}

	std::vector<Texture> textures;

	std::vector<std::string> paths;
	std::string right = "Res/Textures/right.png";
	paths.push_back(right);
	std::string left = "Res/Textures/left.png";
	paths.push_back(left);
	std::string top = "Res/Textures/top.png";
	paths.push_back(top);
	std::string bottom = "Res/Textures/bottom.png";
	paths.push_back(bottom);
	std::string back = "Res/Textures/back.png";
	paths.push_back(back);
	std::string front = "Res/Textures/front.png";
	paths.push_back(front);
	Texture day_cube = Tools::LoadCubeTexture(paths);
	textures.push_back(day_cube);

	paths.clear();
	right = "Res/Textures/nightRight.png";
	paths.push_back(right);
	left = "Res/Textures/nightLeft.png";
	paths.push_back(left);
	top = "Res/Textures/nightTop.png";
	paths.push_back(top);
	bottom = "Res/Textures/nightBottom.png";
	paths.push_back(bottom);
	back = "Res/Textures/nightBack.png";
	paths.push_back(back);
	front = "Res/Textures/nightFront.png";
	paths.push_back(front);
	Texture night_cube = Tools::LoadCubeTexture(paths);
	textures.push_back(night_cube);

	return new Model(new Mesh(vertices, textures));
}

Model* Skybox::GetModel()
{
	return model_;
}

float Skybox::GetRotation()
{
	return rotation_;
}

void Skybox::Rotate()
{
	rotation_ += ROTATE_SPEED;
}


