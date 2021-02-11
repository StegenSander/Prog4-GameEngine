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
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->IsMarkedForDelete())
		{
			m_Objects.erase(m_Objects.begin() + i);
			std::cout << "GameObject Deleted\n";
			i--;
		}
	}
}

