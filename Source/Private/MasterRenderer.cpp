#include "MasterRenderer.h"
#include "Tools.h"
#include "Config.h"
#include "Entity.h"
#include "Model.h"
#include "Camera.h"
#include "StaticShader.h"
#include "TerrainShader.h"
#include "SkyboxShader.h"
#include "WaterShader.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "SkyboxRenderer.h"
#include "WaterRenderer.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

MasterRenderer::MasterRenderer()
{
	m_StaticShader = new StaticShader();
	m_TerrainShader = new TerrainShader();
	m_SkyboxShader = new SkyboxShader();
	m_WaterShader = new WaterShader();
	m_Projection = Tools::GenerateProjectionMatrix();
	m_EntityRenderer = new EntityRenderer(m_StaticShader, m_Projection);
	m_TerrainRenderer = new TerrainRenderer(m_TerrainShader, m_Projection);
	m_SkyboxRenderer = new SkyboxRenderer(m_SkyboxShader, m_Projection);

	EnableCulling();
}

void MasterRenderer::Initialize() const
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(RED, GREEN, BLUE, 1.0f);
}

void MasterRenderer::Render(std::vector<Light*> const& lights, Camera* camera, glm::vec4 const& plane) const
{
	Initialize();

	//Skybox
	m_SkyboxShader->Start();
	m_SkyboxShader->LoadFogColor(glm::vec3(RED, GREEN, BLUE));
	m_SkyboxShader->LoadViewMatrix(m_Skybox, glm::mat4(glm::mat3(camera->GenerateViewMatrix())));
	m_SkyboxRenderer->Render(m_Skybox);
	
	//Entities
	m_StaticShader->Start();
	m_StaticShader->LoadPlane(plane);
	m_StaticShader->LoadSkyColour(glm::vec3(RED, GREEN, BLUE));
	m_StaticShader->LoadLight(lights);
	m_StaticShader->LoadViewMatrix(camera->GenerateViewMatrix());
	m_EntityRenderer->Render(m_Entities);

	//Terrain
	m_TerrainShader->Start();
	m_TerrainShader->LoadPlane(plane);
	m_TerrainShader->LoadSkyColour(glm::vec3(RED, GREEN, BLUE));
	m_TerrainShader->LoadLight(lights);
	m_TerrainShader->LoadViewMatrix(camera->GenerateViewMatrix());
	m_TerrainRenderer->Render(m_Terrain);
}

void MasterRenderer::RenderWater(Camera* camera) const
{
	//Water
	m_WaterShader->Start();
	m_WaterShader->LoadViewMatrix(camera->GenerateViewMatrix());
	m_WaterRenderer->Render(m_Water);
}

void MasterRenderer::ProcessEntity(Entity* entity)
{
	Model* model = entity->GetModel();
	auto search = m_Entities.find(model);
	if (search == m_Entities.end())
	{
		std::vector<Entity*> entities;
		entities.push_back(entity);
		m_Entities.emplace(model, entities);
	}
	else
	{
		search->second.push_back(entity);
	}
}

void MasterRenderer::ProcessTerrain(Terrain* terrain)
{
	m_Terrain.push_back(terrain);
}

void MasterRenderer::ProcessSkybox(Skybox* skybox)
{
	m_Skybox = skybox;
}

void MasterRenderer::ProcessWater(Water* water)
{
	m_Water.push_back(water);
}

void MasterRenderer::EnableCulling() const
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::DisableCulling() const
{
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::LoadFramebuffer(Framebuffer* framebuffer)
{
	m_Framebuffer = framebuffer;
	m_WaterRenderer = new WaterRenderer(m_WaterShader, m_Framebuffer, m_Projection);
}
