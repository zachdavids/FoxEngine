#pragma once

#include <map>
#include <vector>
#include <GLM/mat4x4.hpp>

class Mesh;
class Model;
class Entity;
class StaticShader;

class EntityRenderer
{
public:

	EntityRenderer(StaticShader* shader, glm::mat4 const& projection);
	void InitializeModel(Mesh* mesh);
	void LoadModelMatrix(Entity* entity);
	void UnbindModel() const;
	void EnableCulling() const;
	void DisableCulling() const;
	void Render(std::map<Model*, std::vector<Entity*>> const& entities);

private:

	StaticShader* m_Shader;
	glm::mat4 m_Projection;
};