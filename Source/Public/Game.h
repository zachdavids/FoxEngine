#pragma once

#include "WindowManager.h"
#include "Camera.h"
#include "Model.h"
#include "Mesh.h"
#include "MasterRenderer.h"
#include "Light.h"
#include "Terrain.h"
#include "Player.h"
#include "Skybox.h"
#include "Water.h"
#include "Framebuffer.h"
#include "GUIRenderer.h"

#include <vector>
#include <random>
#include <time.h>

class Game
{
public:
	Game();
	void Run();
private:
	Camera* camera_;
	Terrain* terrain_;
	Player* player_;
	Skybox* skybox_;
	Framebuffer* framebuffer_;
	GUIRenderer* gui_renderer_;
	GUIShader* gui_shader_;
	MasterRenderer* master_renderer_;
	WindowManager* window_manager_;
	std::vector<Entity*> entities_;
	std::vector<Light*> lights_;
	std::vector<Water*> water_;
	std::vector<GUI*> gui_;
	void Init();
	void Render();
	void InitEventHandlers();
	void ProcessInput(GLFWwindow* window, double delta_time);
};
