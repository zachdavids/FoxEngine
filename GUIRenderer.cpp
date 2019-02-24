#include "GUIRenderer.h"

GUIRenderer::GUIRenderer(GUIShader* shader) : shader_(shader)
{
	shader_->Start();
	shader_->Stop();
}

void GUIRenderer::Render(std::vector<GUI*> gui)
{
	shader_->Start();
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
	shader_->Stop();
}

void GUIRenderer::InitializeModel(Mesh* mesh)
{
	glBindVertexArray(mesh->GetVAO());
}

void GUIRenderer::UnbindModel()
{
	glBindVertexArray(0);
}

void GUIRenderer::LoadModelMatrix(GUI* gui)
{
	shader_->LoadTransformationMatrix(Tools::GenerateTransformMatrix(gui->GetPosition(), 0, 0, 0, gui->GetScale()));
}