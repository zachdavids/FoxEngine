#include "SkyboxRenderer.h"
#include "SkyboxShader.h"
#include "Mesh.h"
#include "Skybox.h"
#include "Model.h"

SkyboxRenderer::SkyboxRenderer(SkyboxShader* shader, glm::mat4 const& projection) :
	m_Shader(shader), m_Projection(projection)
{
	m_Shader->Start();
	m_Shader->LoadProjectionMatrix(m_Projection);
	m_Shader->LoadTextures();
	m_Shader->LoadBlendFactor(m_BlendFactor);
	m_Shader->Stop();
}

void SkyboxRenderer::InitializeModel(Mesh* mesh) const
{
	m_Shader->LoadBlendFactor(m_BlendFactor);

	for (int i = 0; i < mesh->GetTextures().size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mesh->GetTextures()[i].id);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mesh->GetVAO());
}

void SkyboxRenderer::UnbindModel() const
{
	glBindVertexArray(0);
}

void SkyboxRenderer::Render(Skybox* skybox) const
{
	Model* model = skybox->GetModel();
	InitializeModel(&model->GetMeshes()[0]);
	glDepthMask(GL_FALSE);
	glDrawArrays(GL_TRIANGLES, 0, model->GetMeshes()[0].GetVerticesCount());
	glDepthMask(GL_TRUE);
	UnbindModel();
}

