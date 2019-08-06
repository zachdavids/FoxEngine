#include "GUIRenderer.h"
#include "GUI.h"
#include "Mesh.h"
#include "Model.h"
#include "GUIShader.h"

GUIRenderer::GUIRenderer(GUIShader* shader) : 
	m_Shader(shader)
{
}

void GUIRenderer::Render(std::vector<GUI*> const& gui) const
{
	m_Shader->Start();
	Model* model = gui[0]->GetModel();
	InitializeModel(&model->GetMeshes()[0]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (GUI* gui_element : gui)
	{	
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gui_element->GetTexture().id_);
		LoadModelMatrix(gui_element);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, model->GetMeshes()[0].GetVerticesCount());
	}
	glDisable(GL_BLEND);
	UnbindModel();
	m_Shader->Stop();
}

void GUIRenderer::InitializeModel(Mesh* mesh) const
{
	glBindVertexArray(mesh->GetVAO());
}

void GUIRenderer::UnbindModel() const
{
	glBindVertexArray(0);
}

void GUIRenderer::LoadModelMatrix(GUI* gui) const
{
	m_Shader->LoadTransformationMatrix(Tools::GenerateTransformMatrix(gui->GetPosition(), glm::vec3(0), gui->GetScale()));
}