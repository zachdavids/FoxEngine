#include "Game.h"

Game::Game()
{
	window_manager_ = new WindowManager();
	master_renderer_ = new MasterRenderer();
	framebuffer_ = new Framebuffer();
	GUI* gui = new GUI(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.25f, 0.25f, 0.0), framebuffer_->GetReflectionTexture());
	gui_.push_back(gui);
	//GUI* gui2 = new GUI(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.25f, 0.25f, 0.0), framebuffer_->GetRefractionTexture());
	//gui_.push_back(gui2);
	master_renderer_->LoadFramebuffer(framebuffer_);
	gui_shader_ = new GUIShader();
	gui_renderer_ = new GUIRenderer(gui_shader_);
	srand(time(NULL));
	InitEventHandlers();
	Run();

}

bool Game::CheckCollision(glm::vec3 position1, glm::vec3 size1, glm::vec3 position2, glm::vec3 size2)
{
	if (position1.x + size1.x < position2.x || position1.x > position2.x + size2.x)
		return false;
	if (position1.y + size1.y < position2.y || position1.y > position2.y + size2.y)
		return false;
	if (position1.z + size1.z < position2.z || position1.z > position2.z + size2.z)
		return false;
	return true;
}

void Game::Run()
{
	Model* arwing = new Model("Res/Models/Arwing/Arwing.obj");
	Model* fighter = new Model("Res/Models/Fighter/Fighter.obj");
	Model* heavy_fighter = new Model("Res/Models/HeavyFighter/HeavyFighter.obj");
	Model* interceptor = new Model("Res/Models/Interceptor/Interceptor.obj");
	Model* rocket = new Model("Res/Models/Rocket/Rocket.obj");


	//Player
	player_ = new Player(arwing, rocket, glm::vec3(200.0f, 1.0f, 200.0f), 0, 0, 0, glm::vec3(0.5f, 0.5f, 0.5f));
	entities_.push_back(player_);

	//Enemy
	for (int i = 0; i < 5; i++)
	{
		Enemy* rocket_enemy_ = new RocketEnemy(player_, interceptor, rocket, glm::vec3(rand() % 800, rand() % 20 + 5, rand() % 800), 0, 0, 0, glm::vec3(0.5f, 0.5f, 0.5f));
		entities_.push_back(rocket_enemy_);
		Enemy* gatling_enemy_ = new LaserEnemy(player_, fighter, rocket, glm::vec3(rand() % 800, rand() % 20 + 5, rand() % 800), 0, 0, 0, glm::vec3(0.5f, 0.5f, 0.5f));
		entities_.push_back(gatling_enemy_);
		Enemy* laser_enemy_ = new LaserEnemy(player_, heavy_fighter, rocket, glm::vec3(rand() % 800, rand() % 20 + 5, rand() % 800), 0, 0, 0, glm::vec3(0.5f, 0.5f, 0.5f));
		entities_.push_back(laser_enemy_);
		//Enemy* rocket_enemy_ = new RocketEnemy(player_, interceptor, rocket, glm::vec3(rand() % 800, rand() % 20 + 5, rand() % 800), 0, 0, 0, glm::vec3(0.5f, 0.5f, 0.5f));
		//entities_.push_back(rocket_enemy_);
		//Enemy* rocket_enemy_ = new RocketEnemy(player_, interceptor, rocket, glm::vec3(rand() % 800, rand() % 20 + 5, rand() % 800), 0, 0, 0, glm::vec3(0.5f, 0.5f, 0.5f));
		//entities_.push_back(rocket_enemy_);
	}

	camera_ = new Camera(player_, glm::vec3(0.0f, 1.0f, 10.0f));

	//Terrain
	terrain_ = new Terrain(0, 0);

	//Skybox
	skybox_ = new Skybox();

	//Light
	Light* sun = new Light(glm::vec3(0, 10000.0f, -7000.0f), glm::vec3(0.4f, 0.4f, 0.4f));
	lights_.push_back(sun);
	Light* light1 = new Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.01f, 0.002));
	Light* light2 = new Light(glm::vec3(200.0f, 10.0f, 200.0f), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 0.01f, 0.002));
	Light* light3 = new Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(1.0f, 0.01f, 0.002));
	lights_.push_back(light1);
	lights_.push_back(light2);
	lights_.push_back(light3);

	//Water
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			Water* water = new Water(i * 100.0f, j * 100.0f, -5.0f);
			water_.push_back(water);
		}
	}

	double current_time = glfwGetTime();
	while (!glfwWindowShouldClose(window_manager_->GetWindow()))
	{
		double new_time = glfwGetTime();
		double frame_time = new_time - current_time;
		current_time = new_time;


		//FBO Reflection
		glEnable(GL_CLIP_DISTANCE0);
		framebuffer_->BindReflectionFBO();
		float distance = 2.0f * (camera_->GetPosition().y - (-5.0f));
		camera_->Translate(glm::vec3(0.0f, -distance, 0.0f));
		camera_->SetPitch(-camera_->GetPitch());
		for (Entity* entity : entities_)
		{
			master_renderer_->ProcessEntity(entity);
			//std::cout << entity->GetSubEntities().size() << std::endl;
			for (Entity* sub_entity : entity->GetSubEntities())
			{
				master_renderer_->ProcessEntity(sub_entity);
			}
		}
		master_renderer_->ProcessTerrain(terrain_);
		master_renderer_->ProcessSkybox(skybox_);
		master_renderer_->Render(lights_, camera_, glm::vec4(0.0f, 1.0f, 0.0f, - (-5.0f)));
		camera_->Translate(glm::vec3(0.0f, distance, 0.0f));
		camera_->SetPitch(-camera_->GetPitch());
		framebuffer_->UnbindFBO();

		//FBO Refraction
		glEnable(GL_CLIP_DISTANCE0);
		framebuffer_->BindRefractionFBO();
		for (Entity* entity : entities_)
		{
			master_renderer_->ProcessEntity(entity);
			//std::cout << entity->GetSubEntities().size() << std::endl;
			for (Entity* sub_entity : entity->GetSubEntities())
			{
				master_renderer_->ProcessEntity(sub_entity);
			}
		}
		master_renderer_->ProcessTerrain(terrain_);
		master_renderer_->ProcessSkybox(skybox_);
		master_renderer_->Render(lights_, camera_, glm::vec4(0.0f, -1.0f, 0.0f, (-5.0f)));
		framebuffer_->UnbindFBO();

		//Render
		glDisable(GL_CLIP_DISTANCE0);
		for (Entity* entity : entities_)
		{
			master_renderer_->ProcessEntity(entity);
			//std::cout << entity->GetSubEntities().size() << std::endl;
			for (Entity* sub_entity : entity->GetSubEntities())
			{
				master_renderer_->ProcessEntity(sub_entity);
			}
		}
		master_renderer_->ProcessTerrain(terrain_);
		master_renderer_->ProcessSkybox(skybox_);
		master_renderer_->Render(lights_, camera_, glm::vec4(0.0f, -1.0f, 0.0f, 10000.0f));
		//temp
		gui_renderer_->Render(gui_);

		//water
		for (Water* water : water_)
		{
			master_renderer_->ProcessWater(water);
		}
		master_renderer_->RenderWater(camera_);
		ProcessInput(window_manager_->GetWindow(), frame_time);

		for (Entity* entity : entities_)
		{
			entity->Update(frame_time);
			total_entities_.push_back(entity);
			for (Entity* sub_entity : entity->GetSubEntities())
			{
				sub_entity->Update(frame_time);
				total_entities_.push_back(sub_entity);
			}
		}

		//Terrain Collision Detection
		float terrain_height = terrain_->GetHeight(player_->GetPosition().x, player_->GetPosition().z);
		if (player_->GetPosition().y < terrain_height)
			player_->SetPosition(glm::vec3(player_->GetPosition().x, terrain_height, player_->GetPosition().z));

		if (player_->GetHP() == 0)
		{
			break;
		}

		glfwSwapBuffers(window_manager_->GetWindow());
		glfwPollEvents();
		total_entities_.clear();
	}
}

void Game::InitEventHandlers()
{
	glfwSetKeyCallback(window_manager_->GetWindow(), KeyCallback);
	//glfwSetInputMode(window_manager_->GetWindow(), GLFW_STICKY_KEYS, 1);
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
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		player_->KeyboardInput(Player::FIRE, delta_time, terrain_);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera_->SetFirstPerson();
	camera_->Move();
}

void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	void* ptr = glfwGetWindowUserPointer(window);
	Game* game = (Game*)ptr;

	/*
	if (key == GLFW_KEY_ESCAPE && action != GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key == GLFW_KEY_W && action != GLFW_RELEASE)
		game->camera_->Move(Camera::FORWARD);
	if (key == GLFW_KEY_S && action != GLFW_RELEASE)
		game->camera_->Move(Camera::BACKWARD);
	if (key == GLFW_KEY_A && action != GLFW_RELEASE)
		game->camera_->Move(Camera::LEFT);
	if (key == GLFW_KEY_D && action != GLFW_RELEASE)
		game->camera_->Move(Camera::RIGHT);
	*/
}

int main(void)
{
	Game starfox;
	return 0;
}