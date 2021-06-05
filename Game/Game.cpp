#include "MiniginPCH.h"
#include <Minigin.h>

#include "SceneManager.h"
#include "GameScene.h"
#include <Scene.h>
#include "FileWriteScene.h"
#include "MainMenuScene.h"

int main()
{
	//std::shared_ptr<dae::Scene> scene{ new FileWriteScene() };
	//dae::SceneManager::GetInstance().RegisterScene(scene);
	//dae::SceneManager::GetInstance().SetActiveScene(scene->GetName());
	{
		std::shared_ptr<GameScene> scene{ new GameScene(1) };
		scene->SetGameMode(GameMode::Coop);
		dae::SceneManager::GetInstance().RegisterScene(scene);
	}
	{
		std::shared_ptr<dae::Scene> scene{ new MainMenuScene() };
		dae::SceneManager::GetInstance().RegisterScene(scene);
		dae::SceneManager::GetInstance().SetActiveScene(scene->GetName());
	}

	dae::Minigin engine;
	engine.Run();
	return 0;
}