#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>

#include "Entity.h"
#include "StaticShader.h"
#include "Config.h"

class EntityRenderer
{
public:
	EntityRenderer(StaticShader* shader, glm::mat4 projection);
	void InitializeModel(Mesh* mesh);
	void LoadModelMatrix(Entity* entity);
	void UnbindModel();
	void EnableCulling();
	void DisableCulling();
	void Render(std::map<Model*, std::vector<Entity*>> entities);
private:
	glm::mat4 projection_;
	StaticShader* shader_;
};