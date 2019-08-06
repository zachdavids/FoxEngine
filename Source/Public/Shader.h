#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Tools.h"

#include <string>
#include <vector>

class Shader
{
public:
	Shader();
	~Shader();
	Shader(std::string vertex_path, std::string fragment_path);
	void Start();
	void Stop();
	void BindAttribute(int index, std::string name);
	void SetBool(std::string name, bool value) const;
	void SetInt(std::string name, int value) const;
	void SetFloat(std::string name, float value) const;
	void SetVector(std::string name, glm::vec3 value) const;
	void SetVec4(std::string name, glm::vec4 value) const;
	void SetMat4(std::string name, glm::mat4 value) const;

private:
	int program_id_;
	int vertex_id_;
	int fragment_id_;
	GLuint LoadShader(std::string path, GLuint type);
	GLuint CreateProgram(GLuint vertex_shader, GLuint fragment_shader);
};
