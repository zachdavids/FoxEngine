#pragma once

#include <glm/glm.hpp>

class Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};
