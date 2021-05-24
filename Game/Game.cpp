#include "MiniginPCH.h"
#include <iostream>
#include <Minigin.h>

#include <TextComponent.h>
#include <ResourceManager.h>

#include "SceneManager.h"
#include "TestScene.h"
#include "GameScene.h"
#include <Scene.h>

int main()
{
	std::shared_ptr<dae::Scene> scene{ new GameScene() };
	dae::SceneManager::GetInstance().RegisterScene(scene);
	dae::SceneManager::GetInstance().SetActiveScene(scene->GetName());

	dae::Minigin engine;
	engine.Run();
	return 0;
}