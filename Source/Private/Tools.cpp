#include "Tools.h"
#include "Config.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <sstream>
#include <fstream>

void Tools::ReadFile(std::string const& path, std::string* output)
{
	std::ifstream stream;
	std::stringstream sstr;

	stream.open(path);
	sstr << stream.rdbuf();
	stream.close();
	*output = sstr.str();
}

void Tools::Tokenize(std::string* input, char delimiter, std::vector<std::string>* substrings)
{
	std::stringstream stream(*input);
	std::string substring;

	while (std::getline(stream, substring, delimiter))
	{
		substrings->push_back(substring);
	}
}

glm::mat4 Tools::GenerateTransformMatrix(glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& scale)
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, scale);
	return transform;
}

glm::mat4 Tools::GenerateProjectionMatrix()
{
	return glm::perspective(glm::radians(FOV), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, NEAR_PLANE, FAR_PLANE);
}

Texture Tools::LoadTexture(std::string const& path, std::string const& type)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, components;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &components, 0);

	GLenum format;
	if (components == 1)
		format = GL_RED;
	else if (components == 3)
		format = GL_RGB;
	else if (components == 4)
		format = GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

	stbi_image_free(data);

	Texture texture;
	texture.id = textureID;
	texture.type = type;
	texture.path = path;
	return texture;
}

Texture Tools::LoadCubeTexture(std::vector<std::string> const& paths, std::string const& type)
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

	int width, height, components;
	for (int i = 0; i < paths.size(); i++)
	{
		unsigned char *data = stbi_load(paths[i].c_str(), &width, &height, &components, 0);

		GLenum format;
		if (components == 1)
			format = GL_RED;
		else if (components == 3)
			format = GL_RGB;
		else if (components == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	Texture texture;
	texture.id = texture_id;
	texture.type = type;
	texture.path = "";
	return texture;
}

//From Christer Ericson's Real-Time Collision Detection
float Tools::CalculateBaryCentric(glm::vec2 const& input, glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float d11 = ((p2.z - p3.z) * (input.x - p3.x) + (p3.x - p2.x) * (input.y - p3.z)) / det;
	float d12 = ((p3.z - p1.z) * (input.x - p3.x) + (p1.x - p3.x) * (input.y - p3.z)) / det;
	float d13 = 1.0f - d11 - d12;
	return d11 * p1.y + d12 * p2.y + d13 * p3.y;
}
