#include "MiniginPCH.h"
#include "Menu.h"
#include "Canvas.h"
#include "Buttons.h"
#include "Time.h"
using namespace Crusade;
void Menu::Load()
{
	std::vector<std::shared_ptr<GameObject>>objects{};

	auto canvas = std::make_shared<GameObject>();
	canvas->AddComponent<Canvas>(std::make_shared<Canvas>());
	auto canvasComp = canvas->GetComponent<Canvas>();
	objects.push_back(canvas);
	
	auto singePlayerButton = canvasComp->AddElement(Vector2f{ 250, 300 });
	singePlayerButton->AddComponent<Button>(std::make_shared<Button>());
	auto buttonComp = singePlayerButton->GetComponent<Button>();
	buttonComp->AddCommandToButton(std::make_shared<SinglePlayerLoad>());
	buttonComp->SetSize(Vector2f{100,15});
	singePlayerButton->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>(CShape2DRender::Shape::Rect,glm::vec2{100,15},true,SDL_Color{255,0,0,255}));
	singePlayerButton->AddComponent<CTextRender>(std::make_shared<CTextRender>("SinglePlayer", "Lingua.otf", 15, SDL_Color{ 255,255,255,255 }));

	auto CoopButton = canvasComp->AddElement(Vector2f{ 250, 250 });
	CoopButton->AddComponent<Button>(std::make_shared<Button>());
	auto buttonCompCoop = CoopButton->GetComponent<Button>();
	buttonCompCoop->AddCommandToButton(std::make_shared<CoopLoad>());
	buttonCompCoop->SetSize(Vector2f{ 100,15 });
	CoopButton->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>(CShape2DRender::Shape::Rect, glm::vec2{ 100,15 }, true, SDL_Color{ 255,0,0,255 }));
	CoopButton->AddComponent<CTextRender>(std::make_shared<CTextRender>("Coop", "Lingua.otf", 15, SDL_Color{ 255,255,255,255 }));

	auto verusButton = canvasComp->AddElement(Vector2f{ 250, 200 });
	verusButton->AddComponent<Button>(std::make_shared<Button>());
	auto verusButtonComp = verusButton->GetComponent<Button>();
	verusButtonComp->AddCommandToButton(std::make_shared<VersusLoad>());
	verusButtonComp->SetSize(Vector2f{ 100,15 });
	verusButton->AddComponent<CShape2DRender>(std::make_shared<CShape2DRender>(CShape2DRender::Shape::Rect, glm::vec2{ 100,15 }, true, SDL_Color{ 255,0,0,255 }));
	verusButton->AddComponent<CTextRender>(std::make_shared<CTextRender>("Verus", "Lingua.otf", 15, SDL_Color{ 255,255,255,255 }));
	verusButton->AddComponent<TestHudElements>(std::make_shared<TestHudElements>());
	
	//ADD LEVEL NAME
	auto name = std::make_shared<GameObject>();
	name->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 250,405,0 }, glm::vec3{}));
	name->AddComponent<CTextRender>(std::make_shared<CTextRender>("Qbert", "Lingua.otf", 20, SDL_Color{ 255 ,0,0,255 }));
	objects.push_back(name);
	
	Add(objects);
}
void TestHudElements::Update()
{
	//SceneManager::GetInstance().GetCurrentScene()->FindObject("Camera")->GetComponent<Camera2D>()->Translate(100 * Time::GetInstance().GetDeltaTime(), 0);
}
