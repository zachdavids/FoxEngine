#pragma once

#include <GLM/mat4x4.hpp>

#include <vector>

class Mesh;
class Terrain;
class TerrainShader;

class TerrainRenderer
{
public:

	TerrainRenderer(TerrainShader* shader, glm::mat4 const& projection);
	void Render(std::vector<Terrain*> const& terrain) const;
	void InitializeModel(Mesh* mesh) const;
	void LoadModelMatrix(Terrain* entity) const;
	void UnbindModel() const;

private:

	TerrainShader* m_Shader;
	glm::mat4 m_Projection;
};