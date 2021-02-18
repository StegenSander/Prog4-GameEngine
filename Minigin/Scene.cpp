#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (GameObject*& object : m_Objects)
	{
		delete object;
	}
}

void Scene::Add(GameObject* object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(GameObject*& object : m_Objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const GameObject* object : m_Objects)
	{
		object->Render();
	}
}

void Scene::DeleteGameObjects()
{
	m_Objects.erase(std::remove_if(m_Objects.begin()
		, m_Objects.end(),
		[](GameObject* pGameObject)
		{
			bool mustDelete = pGameObject->IsMarkedForDelete();
			if (mustDelete) delete  pGameObject;
			return mustDelete;
		}), m_Objects.end());
}

