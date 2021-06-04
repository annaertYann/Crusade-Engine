#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponents.h"
#include "CRigidBody2D.h"
using namespace Crusade;

unsigned int Scene::m_IdCounter = 0;
Scene::Scene() : m_Name("Default") {}
void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_ObjectsToBeAdded.push_back(object);
}
void Scene::Add(const std::vector<std::shared_ptr<GameObject>>& objects)
{
	for (auto object : objects)
	{
		m_ObjectsToBeAdded.push_back(object);
	}
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
	if (m_ObjectsToBeAdded.size() > 0)
	{
		for (auto object : m_ObjectsToBeAdded)
		{
			if (object->GetCTransform() == nullptr) { object->AddComponent<CTransform>(std::make_shared<CTransform>()); }
			if (object->GetComponent<CCollider>() != nullptr) { m_CollisionObjects.push_back(object); }
			m_Objects.push_back(object);
		}
		m_ObjectsToBeAdded.clear();
	}
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
		if (object->GetName()==name && !object->GetRemove())
		{
			return object;
		}
	}
	return std::shared_ptr<GameObject>{nullptr};
}
std::vector<std::shared_ptr<GameObject>> Scene::FindAllObjects(const std::string& name)
{
	std::vector<std::shared_ptr<GameObject>> list;
	for (auto& object : m_Objects)
	{
		if (object->GetName() == name && !object->GetRemove())
		{
			list.push_back(object);
		}
	}
	return list;
}

std::vector<std::shared_ptr<GameObject>> Scene::FindAllObjectsWithTag(const std::string& tag)
{
	std::vector<std::shared_ptr<GameObject>> list{};
	for (auto& object : m_Objects)
	{
		if (!object->GetRemove())
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
	}
	return list;
}
