#pragma once

#include "Tools.h"
#include "Terrain.h"
#include "TerrainShader.h"

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader* shader, glm::mat4 projection);
	void Render(std::vector<Terrain*> terrain);
	void InitializeModel(Mesh * mesh);
	void LoadModelMatrix(Terrain* entity);
	void UnbindModel();
private:
	glm::mat4 projection_;
	TerrainShader* shader_;
};