#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <assert.h>

void dae::SceneManager::Initialise()
{
	for (auto scene : m_SceneMap)
	{
		scene.second->Initialise();
	}
}

void dae::SceneManager::Update()
{
	assert(m_ActiveScene);
	m_ActiveScene->Update();
}

void dae::SceneManager::Render()
{
	assert(m_ActiveScene);
	m_ActiveScene->Render();
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	if (m_SceneMap.find(name) != m_SceneMap.end())
	{
		m_ActiveScene = m_SceneMap[name];
	}
	else
	{
		std::cout << "SceneManager: SetActiveScene > Scene doesn't exist";
	}
}

dae::Scene& dae::SceneManager::GetActiveScene()
{
	return *m_ActiveScene;
}

void dae::SceneManager::RegisterScene(const std::shared_ptr<Scene>& scene)
{
	std::string sceneName = scene->GetName();
	if (m_SceneMap.find(sceneName) == m_SceneMap.end())
	{
		m_SceneMap[sceneName] = scene;
	}
	else
	{
		std::cout << "SceneManager:RegisterScene > Scene already exists";
	}
}

void dae::SceneManager::DestroyMarkedObjects()
{
	m_ActiveScene->DestroyMarkedObjects();
}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
{
	return *m_SceneMap[name].get();
}
