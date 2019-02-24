#include "WaterRenderer.h"

const float WaterRenderer::WAVE_SPEED = 0.001;

WaterRenderer::WaterRenderer(WaterShader* shader, Framebuffer* buffer, glm::mat4 projection) : shader_(shader), buffer_(buffer), projection_(projection)
{
	move_factor_ = 0.0f;
	shader_->Start();
	shader_->LoadTextures();
	shader_->LoadProjectionMatrix(projection_);
	shader_->Stop();
}

void WaterRenderer::Render(std::vector<Water*> water)
{
	for (Water* water_tile : water)
	{
		Model* model = water_tile->GetModel();
		move_factor_ += WAVE_SPEED;
		move_factor_ = fmod(move_factor_, 1.0f);
		shader_->LoadMoveFactor(move_factor_);
		InitializeModel(&model->GetMeshes()[0]);
		LoadModelMatrix(water_tile);
		glDrawArrays(GL_TRIANGLES, 0, model->GetMeshes()[0].GetVerticesCount());
		UnbindModel();
	}
}

void WaterRenderer::InitializeModel(Mesh* mesh)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, buffer_->GetReflectionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, buffer_->GetRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mesh->GetTextures()[0].id_);
	glBindVertexArray(mesh->GetVAO());
}

void WaterRenderer::UnbindModel()
{
	glBindVertexArray(0);
}

void WaterRenderer::LoadModelMatrix(Water* water)
{
	shader_->LoadTransformationMatrix(Tools::GenerateTransformMatrix(glm::vec3(water->GetX(), water->GetHeight(), water->GetZ()),
		0, 0, 0, glm::vec3(Water::TILE_SIZE, Water::TILE_SIZE, Water::TILE_SIZE)));
}
