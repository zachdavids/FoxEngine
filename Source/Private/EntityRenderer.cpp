#include "EntityRenderer.h"
#include "Mesh.h"
#include "Model.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Tools.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

EntityRenderer::EntityRenderer(StaticShader* shader, glm::mat4 const& projection) : 
	m_Shader(shader), 
	m_Projection(projection)
{
	m_Shader->Start();
	m_Shader->LoadProjectionMatrix(m_Projection);
	m_Shader->Stop();
}

void EntityRenderer::Render(std::map<Model*, std::vector<Entity*>> const& entities)
{
	for (auto pair : entities)
	{
		Model* model = pair.first;
		for (int i = 0; i < model->GetMeshes().size(); i++) 
		{
			InitializeModel(&model->GetMeshes()[i]);
			for (Entity* entity : pair.second)
			{
				LoadModelMatrix(entity);
				glDrawElements(GL_TRIANGLES, model->GetMeshes()[i].GetSize(), GL_UNSIGNED_INT, 0);
			}
			UnbindModel();
		}
	}
}

void EntityRenderer::InitializeModel(Mesh* mesh)
{
	for (unsigned int i = 0; i < mesh->GetTextures().size(); i++)
	{
		if (mesh->GetTextures()[i].bTransparent == true)
		{
			DisableCulling();
		}

		m_Shader->LoadFakeLighting(mesh->GetTextures()[i].bFakeLighting);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mesh->GetTextures()[i].id);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mesh->GetVAO());
}

void EntityRenderer::LoadModelMatrix(Entity* entity)
{
	const glm::mat4 transform = Tools::GenerateTransformMatrix(entity->GetPosition(), entity->GetRotation(), entity->GetScale());
	m_Shader->LoadTransformationMatrix(transform);
}

void EntityRenderer::UnbindModel() const
{
	glBindVertexArray(0);
	EnableCulling();
}

void EntityRenderer::EnableCulling() const
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void EntityRenderer::DisableCulling() const
{
	glDisable(GL_CULL_FACE);
}