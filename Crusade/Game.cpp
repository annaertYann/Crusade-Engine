#include "MiniginPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Scripts.h"
#include "Scene.h"
#include "Prefabs.h"
using namespace Crusade;
void Game::LoadGame()const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - FPS");

	//BACKGROUND
	auto object1 = std::make_shared<GameObject>();
	object1->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>(ResourceManager::GetInstance().LoadTexture("background.jpg")));
	scene.Add(object1);

	//TEXTRENDER
	const auto object2 = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	object2->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {80,20,0},{} }});
	object2->AddComponent<CTextRender>(std::make_shared<CTextRender>("Crusade Engine", font, SDL_Color{ 255,255,255,255 }));
	scene.Add(object2);

	//LOGO
	auto object3 = std::make_shared<GameObject>();
	object3->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>(ResourceManager::GetInstance().LoadTexture("logo.png")));
	object3->AddComponent<FPSScript>(std::make_shared<FPSScript>());
	object3->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {216,180,0},{} }});
	scene.Add(object3);

	//FPS
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto object4 = std::make_shared<GameObject>();
	object4->AddComponent<CTextRender>(std::make_shared<CTextRender>("1", fpsFont, SDL_Color{ 255,255,100,255 }));
	object4->AddComponent<FPSScript>(std::make_shared<FPSScript>());
	object4->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ }});
	scene.Add(object4);

	//QBERT
	auto qbert = Qbert::GetInstance().CreateObject({ 200,400,0 });
	scene.Add(qbert);
	//LIVESDISPLAY
	auto livesDisplay = std::make_shared<GameObject>();
	livesDisplay->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {400,20,0},{} }});
	livesDisplay->AddComponent<CTextRender>(std::make_shared<CTextRender>("Lives: " + std::to_string(qbert->GetComponent<Lives>()->GetLives() ), font, SDL_Color{ 255,50,50,255 }));
	livesDisplay->AddComponent<LivesCounter>(std::make_shared<LivesCounter>()); //OBERVER
	scene.Add(livesDisplay);
	
	
}
