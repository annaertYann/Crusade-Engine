#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "../Scene/SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "../Scene/Object/Component/RenderComponents.h"
#include "../Scene/Object/GameObject.h"
#include "../Scene/Scene.h"
#include  "Time.h"
#include "../Scene/Object/Component/FPS.h"
#include "../Scene/Object/Component/ScriptComponents.h"
#include "../Scene/Object/Component/Transform.h"
using namespace std;
using namespace std::chrono;

void Crusade::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Crusade Engine",
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
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - FPS");
	
	auto object1 = std::make_shared<GameObject>();
	object1->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>(ResourceManager::GetInstance().LoadTexture("background.jpg")));
	scene.Add(object1);

	const auto object2 = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	object2->GetComponent<Transform>()->SetPosition(80, 20,0);
	object2->AddComponent<CTextRender>(std::make_shared<CTextRender>("Crusade Engine", font, SDL_Color {255,255,255,255} ));
	scene.Add(object2);

	auto object3 = std::make_shared<GameObject>();
	object3->AddComponent<CTexture2DRender>( std::make_shared<CTexture2DRender>( ResourceManager::GetInstance().LoadTexture("logo.png") ));
	object3->AddComponent<CFPS>(std::make_shared<CFPS>() );
	object3->GetComponent<Transform>()->SetPosition(216, 180, 0);
	scene.Add(object3);

	auto font1 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto object4 = std::make_shared<GameObject>();
	object4->AddComponent<CTextRender>(std::make_shared<CTextRender>("1", font1,SDL_Color{100,255,100,255}));
	object4->AddComponent<CFPS>(std::make_shared<CFPS>());
	object4->AddComponent<DisplayFPS>(std::make_shared<DisplayFPS>());
	object4->GetComponent<Transform>()->SetPosition(0, 0, 0);
	scene.Add(object4);
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
