#pragma once

#include "Texture.h"

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>

#include <vector>

namespace Tools
{
	void ReadFile(std::string const& path, std::string* output);
	void Tokenize(std::string* input, char delimiter, std::vector<std::string>* substrings);
	glm::mat4 GenerateTransformMatrix(glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& scale);
	glm::mat4 GenerateProjectionMatrix();
	Texture LoadTexture(std::string const& path, std::string const& type = "misc");
	Texture LoadCubeTexture(std::vector<std::string> const& paths, std::string const& type = "misc");
	float CalculateBaryCentric(glm::vec2 const& input, glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c);
};
