#include "WaterRenderer.h"
#include "Mesh.h"
#include "Model.h"
#include "Water.h"
#include "WaterShader.h"
#include "Framebuffer.h"
#include "Tools.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const float WaterRenderer::s_WaveSpeed = 0.00001;

WaterRenderer::WaterRenderer(WaterShader* shader, Framebuffer* buffer, glm::mat4 const& projection) : 
	m_Shader(shader), 
	m_Framebuffer(buffer), 
	m_Projection(projection)
{
	m_Shader->Start();
	m_Shader->LoadTextures();
	m_Shader->LoadProjectionMatrix(m_Projection);
	m_Shader->Stop();
}

void WaterRenderer::Render(std::vector<Water*> const& water)
{
	for (Water* water_tile : water)
	{
		Model* model = water_tile->GetModel();
		m_MoveFactor += s_WaveSpeed;
		m_MoveFactor = fmod(m_MoveFactor, 1.0f);
		m_Shader->LoadMoveFactor(m_MoveFactor);
		InitializeModel(&model->GetMeshes()[0]);
		LoadModelMatrix(water_tile);
		glDrawArrays(GL_TRIANGLES, 0, model->GetMeshes()[0].GetVerticesCount());
		UnbindModel();
	}
}

void WaterRenderer::InitializeModel(Mesh* mesh) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Framebuffer->GetReflectionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_Framebuffer->GetRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mesh->GetTextures()[0].id);
	glBindVertexArray(mesh->GetVAO());
}

void WaterRenderer::UnbindModel() const
{
	glBindVertexArray(0);
}

void WaterRenderer::LoadModelMatrix(Water* water) const
{
	const glm::mat4 transform = Tools::GenerateTransformMatrix(
			glm::vec3(water->GetX(), 
			water->GetHeight(), 
			water->GetZ()),
			glm::vec3(0), 
			glm::vec3(Water::s_TileSize, Water::s_TileSize, Water::s_TileSize)
	);

	m_Shader->LoadTransformationMatrix(transform);
}
