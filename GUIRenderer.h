#pragma once

#include "Model.h"
#include "GUIShader.h"
#include "GUI.h"

class GUIRenderer
{
public:
	GUIRenderer(GUIShader* shader);
	void Render(std::vector<GUI*> gui);
private:
	Model* model_;
	GUIShader* shader_;
	void InitializeModel(Mesh * mesh);
	void UnbindModel();
	void LoadModelMatrix(GUI * gui);
};