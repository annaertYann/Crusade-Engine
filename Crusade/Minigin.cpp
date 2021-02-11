#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include  "Time.h"
using namespace std;
using namespace std::chrono;

void Crusade::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void Crusade::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Crusade Engine", font);
	to->SetPosition(80, 20);
	scene.Add(to);
}

void Crusade::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Crusade::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	//GAME LOOP
	{
		//CREATE SINGLETONS
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();
		//CREATE EXIT FLAG
		auto doContinue = true;
		//CREATE TIME VARIABLES
		auto lastTime = std::chrono::high_resolution_clock::now();
		auto lag = 0.0f;
		const auto MsPerUpdate = MsPerFrame / 1000.f;
		const auto deltaTime = std::make_unique<float>( );
		auto currentTime = high_resolution_clock::now();
		//INITIALIZE TIME
		time.Init(lastTime, MsPerUpdate, deltaTime.get());
		
		while (doContinue)
		{
			//ADJUST TIME VARIABLES
			currentTime = high_resolution_clock::now();
			*deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += *deltaTime;
			//INPUT
			doContinue = input.ProcessInput();
			//FIXED UDDATE
			while (lag >= MsPerUpdate)
			{
				sceneManager.FixedUpdate();
				lag -= MsPerUpdate;
			}
			//UPDATE
			sceneManager.Update();
			sceneManager.LateUpdate();
			//RENDER
			renderer.Render();
			//SLEEP
			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
