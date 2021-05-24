#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"

using namespace dae;

Scene::Scene(const std::string& name) 
	: m_Name(name) 
	, m_SceneData{ new SceneData() }
{
	m_SceneData->pInputManager = new InputManager();
	m_SceneData->pInputManager->SetAmountOfControllers(2);
}

Scene::~Scene()
{
	std::cout << "Scene Destructor\n";
}

void Scene::AddObject(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	object->SetScene(this);
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

