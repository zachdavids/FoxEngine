#pragma once

#include <glm/glm.hpp>

class Vertex
{
public:
	glm::vec3 position_;
	glm::vec3 normal_;
	glm::vec2 texture_uv_;
	glm::vec3 tangent_;
	glm::vec3 bitangent_;
};
