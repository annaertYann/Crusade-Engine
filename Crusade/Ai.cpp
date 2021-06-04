#include "MiniginPCH.h"
#include "Ai.h"
using namespace Crusade;
std::shared_ptr<GameObject> Coily::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{

	std::shared_ptr<GameObject> coily{ std::make_shared<GameObject>() };
	coily->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	auto render = std::make_shared<CRender>();
	coily->AddComponent<CRender>(render);
	render->SetCurrentLayer("Front");
	return coily;
}
