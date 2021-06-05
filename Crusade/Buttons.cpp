#include "MiniginPCH.h"
#include "Buttons.h"
#include "SceneManager.h"
void SinglePlayerLoad::Execute()
{
	std::cout << "AAron gay" << std::endl;
	Crusade::SceneManager::GetInstance().LoadScene("Qbert1");
	
}
