#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	std::cout << "Scene Destructor\n";
}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(const std::shared_ptr<GameObject>& object : m_Objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const std::shared_ptr<GameObject>& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::DestroyMarkedObjects()
{
	m_Objects.erase(std::remove_if(m_Objects.begin()
		, m_Objects.end(),
		[](const std::shared_ptr<GameObject>& pGameObject)
		{
			return pGameObject->IsMarkedForDelete();
		}), m_Objects.end());
}

