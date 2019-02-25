#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
{
	static_shader_ = new StaticShader();
	terrain_shader_ = new TerrainShader();
	skybox_shader_ = new SkyboxShader();
	water_shader_ = new WaterShader();
	projection_ = Tools::GenerateProjectionMatrix();
	entity_renderer_ = new EntityRenderer(static_shader_, projection_);
	terrain_renderer_ = new TerrainRenderer(terrain_shader_, projection_);
	skybox_renderer_ = new SkyboxRenderer(skybox_shader_, projection_);

	EnableCulling();
}

void MasterRenderer::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(RED, GREEN, BLUE, 1.0f);
}

void MasterRenderer::Render(std::vector<Light*> lights, Camera * camera, glm::vec4 plane)
{
	Initialize();

	//Skybox
	skybox_shader_->Start();
	skybox_shader_->LoadFogColor(glm::vec3(RED, GREEN, BLUE));
	skybox_shader_->LoadViewMatrix(skybox_, glm::mat4(glm::mat3(camera->GenerateViewMatrix())));
	skybox_renderer_->Render(skybox_);
	skybox_shader_->Stop();
	
	//Entities
	static_shader_->Start();
	static_shader_->LoadPlane(plane);
	static_shader_->LoadSkyColour(glm::vec3(RED, GREEN, BLUE));
	static_shader_->LoadLight(lights);
	static_shader_->LoadViewMatrix(camera->GenerateViewMatrix());
	entity_renderer_->Render(entities_);
	static_shader_->Stop();

	terrain_shader_->Start();
	terrain_shader_->LoadPlane(plane);
	terrain_shader_->LoadSkyColour(glm::vec3(RED, GREEN, BLUE));
	terrain_shader_->LoadLight(lights);
	terrain_shader_->LoadViewMatrix(camera->GenerateViewMatrix());
	terrain_renderer_->Render(terrain_);
	terrain_shader_->Stop();

	entities_.clear();
	terrain_.clear();
}

void MasterRenderer::RenderWater(Camera* camera)
{
	//Water
	water_shader_->Start();
	water_shader_->LoadViewMatrix(camera->GenerateViewMatrix());
	water_renderer_->Render(water_);
	water_shader_->Stop();
	water_.clear();
}

void MasterRenderer::ProcessEntity(Entity* entity)
{
	Model* model = entity->GetModel();
	auto search = entities_.find(model);
	if (search == entities_.end())
	{
		std::vector<Entity*> entities;
		entities.push_back(entity);
		entities_.emplace(model, entities);
	}
	else
	{
		search->second.push_back(entity);
	}
}

void MasterRenderer::ProcessTerrain(Terrain* terrain)
{
	terrain_.push_back(terrain);
}

void MasterRenderer::ProcessSkybox(Skybox* skybox)
{
	skybox_ = skybox;
}

void MasterRenderer::ProcessWater(Water* water)
{
	water_.push_back(water);
}

void MasterRenderer::EnableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::DisableCulling()
{
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::LoadFramebuffer(Framebuffer* buffer)
{
	buffer_ = buffer;
	water_renderer_ = new WaterRenderer(water_shader_, buffer_, projection_);
}
