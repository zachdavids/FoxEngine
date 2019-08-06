#pragma once

#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>

#include <string>

class Shader
{
public:

	Shader(std::string const& vertex_path, std::string const& fragment_path);
	void Start() const;
	void Stop() const;
	void SetBool(std::string const& name, bool value) const;
	void SetInt(std::string const& name, int value) const;
	void SetFloat(std::string const& name, float value) const;
	void SetVector(std::string const& name, glm::vec3 const& value) const;
	void SetVec4(std::string const& name, glm::vec4 const& value) const;
	void SetMat4(std::string const& name, glm::mat4 const& value) const;

private:

	unsigned int LoadShader(std::string const& path, unsigned int type) const;
	unsigned int CreateProgram(unsigned int vertex_shader, unsigned int fragment_shader) const;

private:

	int m_ProgramID;
	int m_VertexID;
	int m_FragmentID;
};
