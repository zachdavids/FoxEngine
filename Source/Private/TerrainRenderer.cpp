#include "TerrainRenderer.h"
#include "TerrainShader.h"
#include "Model.h"
#include "Terrain.h"
#include "Tools.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

TerrainRenderer::TerrainRenderer(TerrainShader* shader, glm::mat4 const& projection) :
	m_Shader(shader), 
	m_Projection(projection)
{
	m_Shader->Start();
	m_Shader->LoadProjectionMatrix(m_Projection);
	m_Shader->LoadTextures();
	m_Shader->Stop();
}

void TerrainRenderer::Render(std::vector<Terrain*> const& terrains) const
{
	for (Terrain* terrain : terrains)
	{
		LoadModelMatrix(terrain);
		Model* model = terrain->GetModel();
		InitializeModel(&model->GetMeshes()[0]);
		for (int i = 0; i < model->GetMeshes().size(); i++) 
		{
			glDrawElements(GL_TRIANGLES, model->GetMeshes()[i].GetSize(), GL_UNSIGNED_INT, 0);
		}
		UnbindModel();
	}
}

void TerrainRenderer::InitializeModel(Mesh* mesh) const
{
	for (unsigned int i = 0; i < mesh->GetTextures().size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mesh->GetTextures()[i].id);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mesh->GetVAO());
}

void TerrainRenderer::LoadModelMatrix(Terrain* terrain) const
{
	//TODO: MOVE GENERATE TRANSFORM TO ENTITY
	glm::mat4 transform_ = Tools::GenerateTransformMatrix(glm::vec3(terrain->GetX(), 0.0f, terrain->GetZ()), glm::vec3(0), glm::vec3(1.0f, 1.0f, 1.0f));
	m_Shader->LoadTransformationMatrix(transform_);
}

void TerrainRenderer::UnbindModel() const
{
	glBindVertexArray(0);
}
