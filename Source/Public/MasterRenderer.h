#pragma once

#include <GLM/mat4x4.hpp>

#include <map>
#include <vector>

class Entity;
class Model;
class Light;
class Camera;
class Terrain;
class Skybox;
class Water;
class Framebuffer;
class StaticShader;
class TerrainShader;
class SkyboxShader;
class WaterShader;
class EntityRenderer;
class TerrainRenderer;
class SkyboxRenderer;
class WaterRenderer;
class GUIRenderer;

class MasterRenderer
{
public:

	MasterRenderer();
	void Initialize() const;
	void Render(std::vector<Light*> const& lights, Camera* camera, glm::vec4 const& plane) const;
	void RenderWater(Camera* camera) const;
	void ProcessEntity(Entity* entity);
	void ProcessTerrain(Terrain* terrain);
	void ProcessSkybox(Skybox* skybox);
	void ProcessWater(Water* water);
	void EnableCulling() const;
	void DisableCulling() const;
	void LoadFramebuffer(Framebuffer* framebuffer);

private:

	StaticShader* m_StaticShader;
	TerrainShader* m_TerrainShader;
	SkyboxShader* m_SkyboxShader;
	WaterShader* m_WaterShader;
	EntityRenderer* m_EntityRenderer;
	TerrainRenderer* m_TerrainRenderer;
	SkyboxRenderer* m_SkyboxRenderer;
	WaterRenderer* m_WaterRenderer;
	GUIRenderer* m_GUIRenderer;
	Framebuffer* m_Framebuffer;
	Skybox* m_Skybox;
	glm::mat4 m_Projection;
	std::map<Model*, std::vector<Entity*>> m_Entities;
	std::vector<Terrain*> m_Terrain;
	std::vector<Water*> m_Water;
};