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
	//TEST SCENE
	{
		auto& scene = SceneManager::GetInstance().CreateScene("Exercise - FPS");
		std::cout << "XX TO Many" << std::endl;
		std::cout << "PRESS NUMPAD 1 AND 4 TO KILL QBERTS" << std::endl;
		std::cout << "PRESS NUMPAD 2 AND 5 TO GIVE QBERTS POINTS" << std::endl;
		//CAMERA
		auto camera = std::make_shared<GameObject>();
		camera->AddComponent<Camera2D>(std::make_shared<Camera2D>(Point2f{ 0,0 }, Renderer::GetInstance().GetWindowSize()));
		camera->SetName("Camera");
		scene.Add(camera);

		//BACKGROUND
		auto object1 = std::make_shared<GameObject>();
		object1->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>("background.jpg"));
		scene.Add(object1);

		////TEXTRENDER
		const auto object2 = std::make_shared<GameObject>();
		std::string font = "Lingua.otf";
		auto ptSize = 40;
		object2->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {80,400,0},{} }});
		object2->AddComponent<CTextRender>(std::make_shared<CTextRender>("Crusade Engine", font, ptSize, SDL_Color{ 1,1,1,1 }, glm::vec2{ 200,40 }));
		scene.Add(object2);

		//LOGO
		auto object3 = std::make_shared<GameObject>();
		object3->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>("logo.png"));
		object3->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {216,280,0},{} }});
		scene.Add(object3);

		//FPS
		auto object4 = std::make_shared<GameObject>();
		object4->AddComponent<CTextRender>(std::make_shared<CTextRender>("1", font, ptSize, SDL_Color{ 0,0,1,1 }, glm::vec2{ 40,40 }));
		object4->AddComponent<FPSScript>(std::make_shared<FPSScript>());
		object4->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ glm::vec3{0,440,0},{} }});
		scene.Add(object4);

		//QBERT
		auto qBert = QBert::GetInstance().CreateObject({ 200,400,0 }, { 0,0,90 });
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
		livesDisplay->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {400,350,0},{} }});
		livesDisplay->AddComponent<CTextRender>(std::make_shared<CTextRender>("Lives: ", font, ptSize, SDL_Color{ 1,1,1,1 }, glm::vec2{ 100,40 }));
		livesDisplay->AddComponent<LivesCounter>(std::make_shared<LivesCounter>(3)); //OBERVER
		scene.Add(livesDisplay);

		//score display
		auto ScoreDisplay = std::make_shared<GameObject>();
		ScoreDisplay->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {400,400,0},{} }});
		ScoreDisplay->AddComponent<CTextRender>(std::make_shared<CTextRender>("Score: 0", font, ptSize, SDL_Color{ uint8_t(50 / 255.f),1, uint8_t(50 / 255.f),1 }, glm::vec2{ 100,40 }));
		ScoreDisplay->AddComponent<PointsCounter>(std::make_shared<PointsCounter>()); //OBERVER
		scene.Add(ScoreDisplay);

		//BOUNCING BALL
		auto ball = std::make_shared<GameObject>();
		ball->AddComponent<CRender>(std::make_shared<CRender>());
		ball->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {500,100,0},{} }});
		ball->AddComponent<CRectCollider>(std::make_shared<CRectCollider>(Rectf{ 0,0,50,50 }));
		ball->AddComponent<CRigidBody2D>(std::make_shared<CRigidBody2D>());
		ball->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>("QBert/Idle.png"));
		//ball->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>( CShape2DRender::Shape::Circle,glm::vec2{50,50},false,SDL_Color{255,0,0,255} ) );
		ball->GetComponent<CTexture2DRender>()->SetDestDimensions(50, 50);
		ball->GetComponent<CRigidBody2D>()->SetVelocity({ -100,400 });
		ball->GetComponent<CRigidBody2D>()->SetGravityEnabled(false);
		ball->AddComponent<MoveInput>(std::make_shared<MoveInput>());
		ball->SetName("Ball");
		scene.Add(ball);

		//ADD FLOOR
		auto floor = std::make_shared<GameObject>();
		floor->AddComponent<CRender>(std::make_shared<CRender>());
		floor->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {-100,0,0},{} }});
		floor->AddComponent<CRectCollider>(std::make_shared<CRectCollider>(Rectf{ 0,0,1000,10 }));
		//floor->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>(ResourceManager::GetInstance().LoadTexture("block.png")));
		floor->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>(CShape2DRender::Shape::Rect, glm::vec2{ 1000,10 }, false, SDL_Color{ 1,0,0,1 }));
		//floor->GetComponent<CTexture2DRender>()->SetDestDimensions(1000, 10);
		scene.Add(floor);

		//ADD FLOOR
		auto floor1 = std::make_shared<GameObject>();
		floor1->AddComponent<CRender>(std::make_shared<CRender>());
		floor1->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {-100,280,0},{} }});
		floor1->AddComponent<CRectCollider>(std::make_shared<CRectCollider>(Rectf{ 0,0,1000,10 }));
		//floor->AddComponent<CTexture2DRender>(std::make_shared<CTexture2DRender>(ResourceManager::GetInstance().LoadTexture("block.png")));
		floor1->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>(CShape2DRender::Shape::Rect, glm::vec2{ 1000,10 }, false, SDL_Color{ 1,0,0,1 }));
		//floor->GetComponent<CTexture2DRender>()->SetDestDimensions(1000, 10);
		scene.Add(floor1);
	}
	//QBERT GAME
	{
		auto& scene = SceneManager::GetInstance().CreateScene("Qbert");
		//CAMERA
		auto camera = std::make_shared<GameObject>();
		camera->AddComponent<Camera2D>(std::make_shared<Camera2D>(Point2f{ 0,0 }, Renderer::GetInstance().GetWindowSize()));
		camera->SetName("Camera");
		scene.Add(camera);

		const auto render = camera->GetComponent<Camera2D>()->GetOriginalWindow();
		const float hexaSize{ render.width / 8 };
		for (int j{}; j < 8; j++)
		{
			for (int i{}; i < 8; i++)
			{
				if (j % 2 == 0)
				{
					//ADD HEXAGON
					auto HEXAGON = std::make_shared<GameObject>();
					HEXAGON->AddComponent<CRender>(std::make_shared<CRender>());
					HEXAGON->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {i * hexaSize,j * hexaSize * 3 / 4,0},{} }});
					HEXAGON->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>(CShape2DRender::Shape::Hexagon, glm::vec2{ hexaSize,hexaSize }, false, SDL_Color{ 1,0,0,1 }));
					HEXAGON->AddComponent<CCollider>(std::make_shared<cHexagonCollider>(Rectf{ 0,0,hexaSize,hexaSize }));
					scene.Add(HEXAGON);
				}
				else
				{
					//ADD HEXAGON
					auto HEXAGON = std::make_shared<GameObject>();
					HEXAGON->AddComponent<CRender>(std::make_shared<CRender>());
					HEXAGON->AddComponent<CTransform>(std::shared_ptr<CTransform>{new CTransform{ {i * hexaSize + hexaSize / 2,j * hexaSize * 3 / 4,0},{} }});
					HEXAGON->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>(CShape2DRender::Shape::Hexagon, glm::vec2{ hexaSize,hexaSize }, false, SDL_Color{ 1,0,0,1 }));
					HEXAGON->AddComponent<CCollider>(std::make_shared<cHexagonCollider>(Rectf{ 0,0,hexaSize,hexaSize }));
					scene.Add(HEXAGON);
				}
			}
		}
	}
	//SET CURRENT SCENE
	SceneManager::GetInstance().SetCurrentScene("Qbert");
}
