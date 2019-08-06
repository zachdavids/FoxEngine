#include "Skybox.h"
#include "Tools.h"

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
		vertex.position = vector;
		vector = glm::vec3(1.0f);
		vertex.uv = uv;
		vertex.normal = vector;
		vertex.tangent = vector;
		vertex.bitangent = vector;
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


