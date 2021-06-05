#include "MiniginPCH.h"
#include "QbertGame.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Levels.h"
#include "RenderComponents.h"
#include "Menu.h"
using namespace Crusade;
void QbertGame::LoadGame()const
{
	auto& sceneManager = SceneManager::GetInstance();
	//SET LAYERS
	CRender::AddNewLayer("Back");
	CRender::AddNewLayer("Middle");
	CRender::AddNewLayer("Front");
	sceneManager.CreateScene<Level1>("Qbert1");
	sceneManager.CreateScene<Level2>("Qbert2");
	sceneManager.CreateScene<Level3>("Qbert3");
	sceneManager.CreateScene<Menu>("Menu");
	sceneManager.LoadScene("Menu");
}
