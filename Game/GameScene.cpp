#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"


//Components
#include "TextureComponent.h"
#include "LevelComponent.h"

GameScene::GameScene()
	: Scene("GameScene")
{
}

void GameScene::Initialise()
{
	using namespace dae;
	std::cout << "GameScene Initialised\n";


	{
		std::shared_ptr<GameObject> background{ new GameObject() };
		std::shared_ptr<TextureComponent> backgroundTexture(new TextureComponent{ "background.jpg" });
		background->AddComponent(backgroundTexture);
		AddObject(background);
	}

	{
		std::shared_ptr<GameObject> level{ new GameObject() };
		std::shared_ptr<LevelComponent> levelComponent(new LevelComponent{ 7,64 });
		level->AddComponent(levelComponent);
		AddObject(level);

		//Only call this after the object is added to the scene
		level->GetTransform().SetPosition({ 260,0,0 });
		levelComponent->CreateLevel();
	}
}
