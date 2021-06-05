#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputManager.h"

using namespace dae;

Scene::Scene(const std::string& name) 
	: m_Name(name) 
	, m_SceneData{ new SceneData() }
	, m_MustReset{ false }
{
	m_SceneData->pInputManager = new InputManager();
	m_SceneData->pInputManager->SetAmountOfControllers(2);
}

Scene::~Scene()
{
	m_Objects.clear();
	delete m_SceneData->pInputManager;
	delete m_SceneData;
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

void dae::Scene::Reset()
{
	m_MustReset = true;
}

void Scene::PostUpdate()
{
	if (m_MustReset)
	{
		for (const std::shared_ptr<GameObject>& object : m_Objects)
		{
			object->SetScene(nullptr);
		}
		{
			m_Objects.clear();
		}

		OnReset();

		delete m_SceneData->pInputManager;
		m_SceneData->pInputManager = new InputManager();
		m_SceneData->pInputManager->SetAmountOfControllers(2);

		Initialise();

		m_MustReset = false;
	}

	m_Objects.erase(std::remove_if(m_Objects.begin()
		, m_Objects.end(),
		[](const std::shared_ptr<GameObject>& pGameObject)
		{
			return pGameObject->IsMarkedForDelete();
		}), m_Objects.end());
}

