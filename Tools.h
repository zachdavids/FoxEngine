#pragma once

#include "Config.h"
#include "Texture.h"
#include "stb_image.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

class Tools
{
public:
	static void ReadFile(std::string path, std::string* );
	static void Tokenize(std::string* input, char delimiter, std::vector<std::string>* substrings);
	static glm::mat4 GenerateTransformMatrix(glm::vec3 position, float pitch, float yaw, float roll, glm::vec3 scale);
	static glm::mat4 GenerateProjectionMatrix();
	static Texture LoadTexture(std::string path, std::string type = "misc");
	static Texture LoadCubeTexture(std::vector<std::string> paths, std::string type = "misc");
	static float CalculateBaryCentric(glm::vec2 input, glm::vec3 a, glm::vec3 b, glm::vec3 c);
};
