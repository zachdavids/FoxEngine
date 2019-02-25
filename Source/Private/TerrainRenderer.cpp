#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(TerrainShader* shader, glm::mat4 projection) : shader_(shader), projection_(projection)
{
	shader_->Start();
	shader_->LoadProjectionMatrix(projection_);
	shader_->LoadTextures();
	shader_->Stop();
}

void TerrainRenderer::Render(std::vector<Terrain*> terrains)
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

void TerrainRenderer::InitializeModel(Mesh* mesh)
{
	for (unsigned int i = 0; i < mesh->GetTextures().size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mesh->GetTextures()[i].id_);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mesh->GetVAO());
}

void TerrainRenderer::LoadModelMatrix(Terrain* terrain)
{
	//TODO: MOVE GENERATE TRANSFORM TO ENTITY
	glm::mat4 transform_ = Tools::GenerateTransformMatrix(glm::vec3(terrain->GetX(), 0.0f, terrain->GetZ()), 0, 0, 0, glm::vec3(1.0f, 1.0f, 1.0f));
	shader_->LoadTransformationMatrix(transform_);
}

void TerrainRenderer::UnbindModel()
{
	glBindVertexArray(0);
}
