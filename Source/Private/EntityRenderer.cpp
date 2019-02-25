#include "EntityRenderer.h"

EntityRenderer::EntityRenderer(StaticShader* shader, glm::mat4 projection) : shader_(shader), projection_(projection)
{
	shader_->Start();
	shader_->LoadProjectionMatrix(projection_);
	shader_->Stop();
}

void EntityRenderer::Render(std::map<Model*, std::vector<Entity*>> entities)
{
	for (auto pair : entities)
	{
		Model* model = pair.first;
		for (int i = 0; i < model->GetMeshes().size(); i++) {
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
		if (mesh->GetTextures()[i].GetTransparent() == true)
			DisableCulling();
		shader_->LoadFakeLighting(mesh->GetTextures()[i].GetFakeLighting());
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mesh->GetTextures()[i].id_);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mesh->GetVAO());
}

void EntityRenderer::LoadModelMatrix(Entity* entity)
{
	shader_->LoadTransformationMatrix(Tools::GenerateTransformMatrix(entity->GetPosition(), 
		entity->GetPitch(), entity->GetYaw(), entity->GetRoll(), entity->GetScale()));
}

void EntityRenderer::UnbindModel()
{
	glBindVertexArray(0);
	EnableCulling();
}

void EntityRenderer::EnableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void EntityRenderer::DisableCulling()
{
	glDisable(GL_CULL_FACE);
}
