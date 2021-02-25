#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponents.h"
using namespace Crusade;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}


void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	object->AddComponent<CTransform>(std::make_shared<CTransform>());
	m_Objects.push_back(object);
}
void Scene::FixedUpdate()
{

}
void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}
void Scene::LateUpdate( )
{
	//REMOVE DEAD OBJECTS FROM OBJECTLIST
	if (m_Objects.size() > 0)
	{
		m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [&](const std::shared_ptr<GameObject>& object)
		{
			return object->GetRemove();
		}), m_Objects.end());
	}
}
void Scene::Render() const
{
	for (auto& object : m_Objects)
	{
		const auto cRender = object->GetCRender();
		if (cRender !=nullptr)
		{
			cRender->RenderObject();
		}
	}
	
}
std::shared_ptr<GameObject> Scene::FindObject(const std::string& name)
{
	for (auto& object : m_Objects)
	{
		if (object->GetName()==name)
		{
			return object;
		}
	}
	return std::shared_ptr<GameObject>{nullptr};
}

