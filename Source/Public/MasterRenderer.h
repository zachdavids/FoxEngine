#pragma once

#include "Config.h"
#include "StaticShader.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"
#include "GUIRenderer.h"
#include "Camera.h"

class MasterRenderer
{
public:
	MasterRenderer();
	void Initialize();
	void Render(std::vector<Light*> lights, Camera* camera, glm::vec4 plane);
	void RenderWater(Camera * camera);
	void ProcessEntity(Entity* entity);
	void ProcessTerrain(Terrain* terrain);
	void ProcessSkybox(Skybox * skybox);
	void ProcessWater(Water* water);
	void EnableCulling();
	void DisableCulling();
	void LoadFramebuffer(Framebuffer* buffer);
private:
	glm::mat4 projection_;

	StaticShader* static_shader_;
	TerrainShader* terrain_shader_;
	SkyboxShader* skybox_shader_;
	WaterShader* water_shader_;

	EntityRenderer* entity_renderer_;
	TerrainRenderer* terrain_renderer_;
	SkyboxRenderer* skybox_renderer_;
	WaterRenderer* water_renderer_;
	GUIRenderer* gui_renderer_;
	Framebuffer* buffer_;

	Skybox* skybox_;
	std::map<Model*, std::vector<Entity*>> entities_;
	std::vector<Terrain*> terrain_;
	std::vector<Water*> water_;
};