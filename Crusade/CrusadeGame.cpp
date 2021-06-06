#include "MiniginPCH.h"
#include "CrusadeGame.h"
#include "GameObject.h"
#include "Scene.h"
using namespace Crusade;
void CrusadeGame::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene<DefaultScene>("Default");
	SceneManager::GetInstance().LoadScene("Default");
	std::vector<std::shared_ptr<GameObject>>objects{};
	//ADD LEVEL NAME
	auto name = std::make_shared<GameObject>();
	name->AddComponent<CTransform>(std::make_shared<CTransform>(glm::vec3{ 30,425,0 }, glm::vec3{}));
	name->AddComponent<CTextRender>(std::make_shared<CTextRender>("Crusade Engine", "Lingua.otf", 20, SDL_Color{ 255 ,0,0,255 }));
	objects.push_back(name);
	scene.Add(objects);
}
