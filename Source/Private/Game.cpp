#include "Game.h"
#include "GUI.h"
#include "GUIShader.h"

Game::Game()
{
	window_manager_ = new WindowManager();
	master_renderer_ = new MasterRenderer();
	framebuffer_ = new Framebuffer();
	GUI* gui = new GUI(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.25f, 0.25f, 0.0), framebuffer_->GetReflectionTexture());
	gui_.push_back(gui);
	master_renderer_->LoadFramebuffer(framebuffer_);
	gui_shader_ = new GUIShader();
	gui_renderer_ = new GUIRenderer(gui_shader_);
	srand(time(NULL));
	Init();
}

void Game::Run()
{
	double current_time = glfwGetTime();
	double lag = 0.0;
	double t = 0.0;
	const double dt = 0.01;
	while (!glfwWindowShouldClose(window_manager_->GetWindow()))
	{
		double new_time = glfwGetTime();
		double frame_time = new_time - current_time;
		current_time = new_time;

		lag += frame_time;
		while (lag >= dt)
		{
			//Collision
			float terrain_height = terrain_->GetHeight(player_->GetPosition().x, player_->GetPosition().z);
			if (player_->GetPosition().y < terrain_height)
			{
				player_->SetPosition(glm::vec3(player_->GetPosition().x, terrain_height, player_->GetPosition().z));
			}

			//Input
			ProcessInput(window_manager_->GetWindow(), frame_time);

			//Update
			for (Entity* entity : entities_)
			{
				entity->Update(dt);
			}

			lag -= dt;
			t += dt;
		}

		//Render
		Render();

		glfwSwapBuffers(window_manager_->GetWindow());
		glfwPollEvents();
	}
}

void Game::Init()
{
	InitEventHandlers();

	Model* arwing = new Model("Resources/Models/Arwing/Arwing.obj");
	player_ = new Player(arwing, glm::vec3(200.0f, 20.0f, 200.0f), 0, 0, 0, glm::vec3(0.5f, 0.5f, 0.5f));
	entities_.push_back(player_);
	for (Entity* entity : entities_)
	{
		master_renderer_->ProcessEntity(entity);
	}

	terrain_ = new Terrain(0, 0);
	master_renderer_->ProcessTerrain(terrain_);

	skybox_ = new Skybox();
	master_renderer_->ProcessSkybox(skybox_);

	Light* sun = new Light(glm::vec3(0, 10000.0f, -7000.0f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(1.0f, 0, 0));
	lights_.push_back(sun);
	Light* light1 = new Light(glm::vec3(250.0f, 10.0f, 250.0f), glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.01f, 0.002));
	Light* light2 = new Light(glm::vec3(200.0f, 10.0f, 200.0f), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 0.01f, 0.002));
	Light* light3 = new Light(glm::vec3(150.0f, 10.0f, 150.0f), glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(1.0f, 0.01f, 0.002));
	lights_.push_back(light1);
	lights_.push_back(light2);
	lights_.push_back(light3);

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			Water* water = new Water(i * 100.0f, j * 100.0f, -5.0f);
			water_.push_back(water);
			master_renderer_->ProcessWater(water);
		}
	}

	camera_ = new Camera(player_, glm::vec3(0.0f, 1.0f, 10.0f));
}

void Game::Render()
{
	//FBO Reflection
	glEnable(GL_CLIP_DISTANCE0);
	framebuffer_->BindReflectionFBO();
	float distance = 2.0f * (camera_->GetPosition().y - (-5.0f));
	camera_->Translate(glm::vec3(0.0f, -distance, 0.0f));
	camera_->SetPitch(-camera_->GetRotation().x);
	master_renderer_->Render(lights_, camera_, glm::vec4(0.0f, 1.0f, 0.0f, -(-5.0f)));
	camera_->Translate(glm::vec3(0.0f, distance, 0.0f));
	camera_->SetPitch(-camera_->GetRotation().x);
	framebuffer_->UnbindFBO();

	//FBO Refraction
	glEnable(GL_CLIP_DISTANCE0);
	framebuffer_->BindRefractionFBO();
	master_renderer_->Render(lights_, camera_, glm::vec4(0.0f, -1.0f, 0.0f, (-5.0f)));
	framebuffer_->UnbindFBO();

	//Rendering
	glDisable(GL_CLIP_DISTANCE0);
	master_renderer_->Render(lights_, camera_, glm::vec4(0.0f, -1.0f, 0.0f, 10000.0f));
	gui_renderer_->Render(gui_);
	master_renderer_->RenderWater(camera_);
}

void Game::InitEventHandlers()
{
	glfwSetWindowUserPointer(window_manager_->GetWindow(), (void *)this);
}

void Game::ProcessInput(GLFWwindow * window, double delta_time)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, 640 / 2, 480 / 2);
	player_->MouseInput((640 / 2) - xpos, (480 / 2) - ypos, delta_time);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		player_->KeyboardInput(Player::FORWARD, delta_time, terrain_);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		player_->KeyboardInput(Player::BACKWARD, delta_time, terrain_);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		player_->KeyboardInput(Player::LEFT, delta_time, terrain_);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		player_->KeyboardInput(Player::RIGHT, delta_time, terrain_);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		player_->KeyboardInput(Player::UP, delta_time, terrain_);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		player_->KeyboardInput(Player::DOWN, delta_time, terrain_);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera_->ToggleCameraMode();
	camera_->Move();
}

int main(void)
{
	Game starfox;
	starfox.Run();
	return 0;
}