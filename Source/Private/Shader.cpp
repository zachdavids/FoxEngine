#include "Shader.h"
#include "Tools.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <iostream>

Shader::Shader(std::string const& vertex_path, std::string const& fragment_path)
{
	m_VertexID = LoadShader(vertex_path, GL_VERTEX_SHADER);
	m_FragmentID = LoadShader(fragment_path, GL_FRAGMENT_SHADER);
	m_ProgramID = CreateProgram(m_VertexID, m_FragmentID);
}

void Shader::Start() const
{
	glUseProgram(m_ProgramID);
}

void Shader::Stop() const
{
	glUseProgram(0);
}

void Shader::SetBool(std::string const& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), (int)value);
}

void Shader::SetInt(std::string const& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}

void Shader::SetFloat(std::string const& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}

void Shader::SetVector(std::string const& name, glm::vec3 const& value) const
{
	glUniform3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVec4(std::string const& name, glm::vec4 const& value) const
{
	glUniform4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetMat4(std::string const& name, glm::mat4 const& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int Shader::LoadShader(std::string const& path, unsigned int type) const
{
	// Read shader text file
	std::string code;
	Tools::ReadFile(path, &code);

	// Compile shader
	const char* vertex_code = code.c_str();
	GLuint shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &vertex_code, NULL);
	glCompileShader(shader_id);

	// Check compile status
	GLint status;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shader_id, maxLength, &maxLength, &infoLog[0]);

		for (int i = 0; i < infoLog.size(); i++)
		{
			std::cout << infoLog[i];
		}
		glDeleteProgram(shader_id);
	}
	return shader_id;
}

unsigned int Shader::CreateProgram(unsigned int vertex_shader, unsigned int fragment_shader) const
{
	unsigned int program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader);
	glAttachShader(program_id, fragment_shader);
	glLinkProgram(program_id);

	GLint status;
	glGetProgramiv(program_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program_id, maxLength, &maxLength, &infoLog[0]);

		for (int i = 0; i < infoLog.size(); i++) {
			std::cout << infoLog[i];
		}
		glDeleteProgram(program_id);
	}
	return program_id;
}
