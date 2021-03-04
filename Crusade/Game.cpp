#include "MiniginPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Scripts.h"
#include "Scene.h"
#include "Prefabs.h"
#include "CRigidBody2D.h"
#include "Camera2D.h"
#include "Renderer.h"
using namespace Crusade;
void Game::LoadGame()const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - FPS");
	std::cout << "XX TO Many" << std::endl;
	std::cout << "PRESS NUMPAD 1 AND 4 TO KILL QBERTS" << std::endl;
	std::cout << "PRESS NUMPAD 2 AND 5 TO GIVE QBERTS POINTS" << std::endl;

	//BACKGROUND
	auto object1 = std::make_shared<GameObject>();
	object1->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>(ResourceManager::GetInstance().LoadTexture("background.jpg")));
	scene.Add(object1);
	
	//BOUNCING BALL
	auto ball = std::make_shared<GameObject>();
	ball->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {500,100,0},{} }});
	ball->AddComponent<CRigidBody2D>(std::make_shared<CRigidBody2D>());
	ball->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>(ResourceManager::GetInstance().LoadTexture("QBert/Idle.png")));
	//ball->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>( CShape2DRender::Shape::Circle,glm::vec2{50,50},false,SDL_Color{255,0,0,255} ) );
	ball->GetComponent<CTexture2DRender>()->SetDestDimensions(50, 50);
	ball->AddComponent<Camera2D>(std::make_shared<Camera2D>(Point2f{ 0,0 }, Renderer::GetInstance().GetWindowSize()));
	ball->SetName("Camera");
	InputManager::GetInstance().AddButtonInput(new InputButtonAction{ InputButtonState::pressed,std::make_unique<Jump>(ball.get()),0,-1,SDL_SCANCODE_SPACE });
	scene.Add(ball);
	
	////TEXTRENDER
	const auto object2 = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	object2->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {80,20,0},{} }});
	object2->AddComponent<CTextRender>(std::make_shared<CTextRender>("Crusade Engine", font, SDL_Color{ 255,255,255,255 }));
	scene.Add(object2);

	//LOGO
	auto object3 = std::make_shared<GameObject>();
	object3->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>(ResourceManager::GetInstance().LoadTexture("logo.png")));
	object3->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {216,180,0},{} }});
	scene.Add(object3);

	//FPS
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 10);
	auto object4 = std::make_shared<GameObject>();
	object4->AddComponent<CTextRender>(std::make_shared<CTextRender>("1", fpsFont, SDL_Color{ 255,255,100,255 }));
	object4->AddComponent<FPSScript>(std::make_shared<FPSScript>());
	object4->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ }});
	scene.Add(object4);

	//QBERT
	auto qBert = QBert::GetInstance().CreateObject({ 200,400,0 },{0,0,90});
	scene.Add(qBert);
	auto qBert2 = QBert::GetInstance().CreateObject({ 200,300,0 });
	qBert2->RemoveComponent<QbertController>();
	qBert2->AddComponent<QbertController>(std::make_shared<QbertController>(SDL_SCANCODE_KP_4, SDL_SCANCODE_KP_5));
	scene.Add(qBert2);

	qBert->SetName("Qbert");
	qBert2->SetName("Qbert");
	qBert->AddTag("Player");
	qBert2->AddTag("Player");
	
	//LIVESDISPLAY
	auto livesDisplay = std::make_shared<GameObject>();
	livesDisplay->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {400,20,0},{} }});
	livesDisplay->AddComponent<CTextRender>(std::make_shared<CTextRender>("Lives: ", font, SDL_Color{ 255,50,50,255 }));
	livesDisplay->AddComponent<LivesCounter>(std::make_shared<LivesCounter>(3)); //OBERVER
	scene.Add(livesDisplay);
	
	//score display
	auto ScoreDisplay = std::make_shared<GameObject>();
	ScoreDisplay->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {400,60,0},{} }});
	ScoreDisplay->AddComponent<CTextRender>(std::make_shared<CTextRender>("Score: 0", font, SDL_Color{ 50,255,50,255 }));
	ScoreDisplay->AddComponent<PointsCounter>(std::make_shared<PointsCounter>()); //OBERVER
	scene.Add(ScoreDisplay);
}
