#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

Shader::Shader(std::string vertex_path, std::string fragment_path)
{
	vertex_id_ = LoadShader(vertex_path, GL_VERTEX_SHADER);
	fragment_id_ = LoadShader(fragment_path, GL_FRAGMENT_SHADER);
	program_id_ = CreateProgram(vertex_id_, fragment_id_);
}

void Shader::Start()
{
	glUseProgram(program_id_);
}

void Shader::Stop()
{
	glUseProgram(0);
}

void Shader::SetBool(std::string name, bool value)
{
	glUniform1i(glGetUniformLocation(program_id_, name.c_str()), (int)value);
}

void Shader::SetInt(std::string name, int value)
{
	glUniform1i(glGetUniformLocation(program_id_, name.c_str()), value);
}

void Shader::SetFloat(std::string name, float value)
{
	glUniform1f(glGetUniformLocation(program_id_, name.c_str()), value);
}

void Shader::SetVector(std::string name, glm::vec3 value)
{
	glUniform3fv(glGetUniformLocation(program_id_, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVec4(std::string name, glm::vec4 value)
{
	glUniform4fv(glGetUniformLocation(program_id_, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetMat4(std::string name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

// Compiles a 'type' shader based on 'path' and returns its ID
GLuint Shader::LoadShader(std::string path, GLuint type)
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
			std::cout << infoLog[i];
		glDeleteProgram(shader_id);
	}
	return shader_id;
}

GLuint Shader::CreateProgram(GLuint vertex_shader, GLuint fragment_shader)
{
	GLuint program_id = glCreateProgram();
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

void Shader::BindAttribute(int index, std::string name)
{
	glBindAttribLocation(program_id_, index, name.c_str());
}

