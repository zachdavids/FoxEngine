#pragma once

#include <vector>

class GUI;
class Mesh;
class Model;
class GUIShader;

class GUIRenderer
{
public:

	GUIRenderer(GUIShader* shader);
	void Render(std::vector<GUI*> const& gui) const;

private:

	void InitializeModel(Mesh* mesh) const;
	void UnbindModel() const;
	void LoadModelMatrix(GUI* gui) const;

private:
	
	Model* m_Model;
	GUIShader* m_Shader;
};