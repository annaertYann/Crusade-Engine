#include "MiniginPCH.h"
#include "Canvas.h"
#include "SceneManager.h"
#pragma warning(disable:26816)
std::shared_ptr<Crusade::GameObject> Crusade::UIElement::CreateObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	std::shared_ptr<GameObject> element{ std::make_shared<GameObject>() };
	
	element->AddComponent<CTransform>(std::make_shared<CTransform>(position, rotation, scale));
	const auto render = std::make_shared<CRender>();
	element->AddComponent<CRender>(render);
	element->AddComponent<UIElementOnScreen>(std::make_shared<UIElementOnScreen>());
	element->SetName("Element");
	return element;
}
void Crusade::UIElementOnScreen::LateUpdate()
{
	m_Transform->SetPosition(m_Camera->GetPosition().x + m_Pos.x,m_Camera->GetPosition().y+m_Pos.y,0);
}
void Crusade::UIElementOnScreen::Start()
{
	m_Transform = m_Owner->GetCTransform();
	auto obj = SceneManager::GetInstance().GetCurrentScene()->FindObject("Camera");
	if(obj)
	{
		auto comp = obj->GetComponent<Camera2D>();
		if(comp)
		{
			m_Camera = comp;
		}
	}
}


Crusade::GameObject* Crusade::Canvas::AddElement(const Vector2f& pos)
{
	const auto obj = UIElement::GetInstance().CreateObject(glm::vec3{pos.x,pos.y,0},{},{1,1,1});
	obj->GetComponent<UIElementOnScreen>()->SetPos(pos);
	SceneManager::GetInstance().GetCurrentScene()->Add(obj);
	m_Elements.push_back(obj.get());
	return obj.get();
}


