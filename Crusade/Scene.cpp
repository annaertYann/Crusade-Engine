#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponents.h"
#include "CRigidBody2D.h"
using namespace Crusade;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}
void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	if (object->GetCTransform() == nullptr) { object->AddComponent<CTransform>(std::make_shared<CTransform>()); }
	if (object->GetComponent<CCollider>() != nullptr) { m_CollisionObjects.push_back(object); }
	m_Objects.push_back(object);
}
void Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
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
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}

	
	//REMOVE DEAD OBJECTS FROM OBJECTLIST
	if (m_Objects.size() > 0)
	{
		m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [&](const std::shared_ptr<GameObject>& object)
		{
			return object->GetRemove();
		}), m_Objects.end());
	}
	//REMOVE DEAD OBJECTS FROM CollisionList
	if (m_CollisionObjects.size() > 0)
	{
		m_CollisionObjects.erase(std::remove_if(m_CollisionObjects.begin(), m_CollisionObjects.end(), [&](const std::shared_ptr<GameObject>& object)
		{
			return object->GetRemove();
		}), m_CollisionObjects.end());
	}
}
void Scene::Render() const
{
	for (auto layer : CRender::GetLayers())
	{
		for (auto& object : m_Objects)
		{
			const auto cRender = object->GetCRender();
			if (cRender != nullptr)
			{
				if (cRender->GetCurrentLayer() == layer.GetLayerNumber())
				{
					cRender->RenderObject();
				}
			}
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

std::vector<std::shared_ptr<GameObject>> Scene::FindAllObjectsWithTag(const std::string& tag)
{
	std::vector<std::shared_ptr<GameObject>> list{};
	for (auto& object : m_Objects)
	{
		for (auto element : object->GetTags())
		{
			if (element == tag)
			{
				list.push_back(object);
				break;
			}
		}
	}
	return list;
}
