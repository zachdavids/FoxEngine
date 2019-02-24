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
	//std::cout << mesh->GetTextures()[0].id_ << std::endl;
	//std::cout << mesh->GetTextures()[1].id_ << std::endl;
	time_ += glfwGetTime() / 1000;
	time_ = std::fmod(time_, 32.0);

	if (time_ >= 0.0f && time_ < 12.0f)
	{
		mesh->GetTextures()[0].id_ = 34;
		mesh->GetTextures()[1].id_ = 34;
		blend_factor_ = (time_ / 12.0f);
	}
	else if (time_ >= 12.0f && time_ < 16.0f)
	{
		mesh->GetTextures()[0].id_ = 34;
		mesh->GetTextures()[1].id_ = 33;
		blend_factor_ = (time_ - 12.0f) / (16.0f - 12.0f);
	}
	else if (time_ >= 16.0f && time_ < 28.0f)
	{
		mesh->GetTextures()[0].id_ = 33;
		mesh->GetTextures()[1].id_ = 33;
		blend_factor_ = (time_ - 16.0f) / (28.0f - 16.0f);
	}
	else
	{
		mesh->GetTextures()[0].id_ = 33;
		mesh->GetTextures()[1].id_ = 34;
		blend_factor_ = (time_ - 28.0f) / (32.0f - 28.0f);
	}
	shader_->LoadBlendFactor(blend_factor_);

	for (int i = 0; i < mesh->GetTextures().size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mesh->GetTextures()[i].id_);
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

