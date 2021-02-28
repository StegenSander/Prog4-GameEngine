#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <assert.h>

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

void dae::SceneManager::SetActiveScene(const std::shared_ptr<Scene>& activeScene)
{
	m_ActiveScene = activeScene;
}

void dae::SceneManager::DestroyMarkedObjects()
{
	m_ActiveScene->DestroyMarkedObjects();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));

	if (!m_ActiveScene) m_ActiveScene = scene;
	m_SceneMap.insert(std::make_pair(name, scene));
	return *scene;
}

dae::Scene& dae::SceneManager::GetScene(const std::string& name)
{
	return *m_SceneMap[name].get();
}
