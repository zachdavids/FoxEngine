#include "SkyboxRenderer.h"

SkyboxRenderer::SkyboxRenderer(SkyboxShader* shader, glm::mat4 projection) : shader_(shader), projection_(projection)
{
	blend_factor_ = 0.5f;
	time_ = 0.0f;
	shader_->Start();
	shader_->LoadProjectionMatrix(projection_);
	shader_->LoadTextures();
	shader_->LoadBlendFactor(blend_factor_);
	shader_->Stop();
}

void SkyboxRenderer::InitializeModel(Mesh* mesh)
{
	shader_->LoadBlendFactor(blend_factor_);

	for (int i = 0; i < mesh->GetTextures().size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mesh->GetTextures()[i].id);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mesh->GetVAO());
}

void SkyboxRenderer::UnbindModel()
{
	glBindVertexArray(0);
}

void SkyboxRenderer::Render(Skybox* skybox)
{
	Model* model = skybox->GetModel();
	InitializeModel(&model->GetMeshes()[0]);
	glDepthMask(GL_FALSE);
	glDrawArrays(GL_TRIANGLES, 0, model->GetMeshes()[0].GetVerticesCount());
	glDepthMask(GL_TRUE);
	UnbindModel();
}

