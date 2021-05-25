#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"


//Components
#include "TextureComponent.h"
#include "LevelComponent.h"
#include "LevelNavigatorComponent.h"
#include "QBertComponent.h"
#include <SDL_scancode.h>
#include "HealthComponent.h"

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

	std::shared_ptr<HealthComponent> healthComponent(new HealthComponent(3));

	std::shared_ptr<GameObject> level{ new GameObject() };
	const int blockSize{ 64 };
	std::shared_ptr<LevelComponent> levelComponent(new LevelComponent{ 7,blockSize,healthComponent });
	{
		level->AddComponent(levelComponent);
		AddObject(level);

		//Only call this after the object is added to the scene
		level->GetTransform().SetPosition({ 260,-50,0 });
		levelComponent->CreateLevel();
	}

	{
		using namespace dae;
		std::shared_ptr<GameObject> qBert{ new GameObject() };
		std::shared_ptr<LevelNavigatorComponent> navigatorComponent(new LevelNavigatorComponent(levelComponent, EntityType::QBert));
		std::shared_ptr<QBertComponent> qbertComponent(new QBertComponent(navigatorComponent,0,healthComponent.get()));
		std::shared_ptr<TextureComponent> textureComponent(new TextureComponent{ "QBert.png",{0,0},{blockSize / 2,blockSize / 2} });
		AddObject(qBert);
		qBert->AddComponent(textureComponent);
		qBert->AddComponent(navigatorComponent);
		qBert->AddComponent(qbertComponent);
		qBert->AddComponent(healthComponent);
		navigatorComponent->MoveToSquare(3, 2);

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_W, ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::NorthEast), qBert.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_A, ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::NorthWest), qBert.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_S, ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::SouthWest), qBert.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_D, ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::SouthEast), qBert.get()));
	}
}
