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
#include "RocketEnemy.h"
#include "LaserEnemy.h"
#include "GatlingEnemy.h"

#include <vector>
#include <random>
#include <time.h>

class Game
{
public:
	Game();
	bool CheckCollision(glm::vec3 position1, glm::vec3 size1, glm::vec3 position2, glm::vec3 size2);
private:
	void Run();
	WindowManager* window_manager_;
	Camera* camera_;
	Model* model_;
	Mesh* mesh_;

	MasterRenderer* master_renderer_;
	Terrain* terrain_;
	Player* player_;
	Skybox* skybox_;
	Framebuffer* framebuffer_;
	std::vector<Entity*> entities_;
	std::vector<Light*> lights_;
	std::vector<Water*> water_;

	std::vector<Entity*> total_entities_;

	std::vector<GUI*> gui_;
	GUIRenderer* gui_renderer_;
	GUIShader* gui_shader_;

	void InitEventHandlers();
	void ProcessInput(GLFWwindow* window, double delta_time);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
