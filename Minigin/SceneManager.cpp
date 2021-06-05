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

	m_IsInitialized = true;
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

bool dae::SceneManager::SetActiveScene(const std::string& name)
{
	if (m_SceneMap.find(name) != m_SceneMap.end())
	{
		m_ActiveScene = m_SceneMap[name];
		return true;
	}

	std::cout << "SceneManager: SetActiveScene > Scene doesn't exist";
	return false;
}

dae::Scene* dae::SceneManager::GetActiveScene()
{
	return m_ActiveScene.get();
}

void dae::SceneManager::RegisterScene(const std::shared_ptr<Scene>& scene)
{
	std::string sceneName = scene->GetName();
	if (m_SceneMap.find(sceneName) == m_SceneMap.end())
	{
		m_SceneMap[sceneName] = scene;
		if(m_IsInitialized) m_SceneMap[sceneName]->Initialise();
	}
	else
	{
		std::cout << "SceneManager:RegisterScene > Scene already exists";
	}
}

void dae::SceneManager::PostUpdate()
{
	m_ActiveScene->PostUpdate();

}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
{
	return *m_SceneMap[name].get();
}
