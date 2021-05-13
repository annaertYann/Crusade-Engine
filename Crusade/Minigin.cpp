#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include  "Time.h"
#include "Game.h"
#include "SDL_Sound_System.h"
#include "ServiceLocator.h"
#include <thread>
using namespace std;
using namespace std::chrono;
void Crusade::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	// Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	m_Window = SDL_CreateWindow(
		"Crusade Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_WindowWidth,
		m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	SDL_GL_CreateContext(m_Window);
	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, m_WindowWidth ,0, m_WindowHeight); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, int(m_WindowWidth), int(m_WindowHeight));

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "Core::Initialize( ), error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
		return;
	}
	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cerr << "Core::Initialize( ), error when calling TTF_Init: " << TTF_GetError() << std::endl;
		return;
	}
	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cerr << "Core::Initialize( ), error when calling IMG_Init: " << IMG_GetError() << std::endl;
		return;
	}
	Renderer::GetInstance().Init(m_Window);
}
void Crusade::Minigin::LoadGame() const
{
	SceneManager::GetInstance().CreateScene<DefaultScene>("DefaultScene");
	if (!m_Game){std::cout << "No game found : Crusade Engine" << std::endl;}
	else
	{m_Game->LoadGame();}
}
void Crusade::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	delete m_Game;
	SDL_Quit();
}
void Crusade::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	//REGISTER SERVICES
	ServiceLocator::GetInstance().RegisterSoundSystem(new SDL_Sound_System());
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
		auto lastTime = high_resolution_clock::now();
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

