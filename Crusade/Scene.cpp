#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace Crusade;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}


void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
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

}
void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

