#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"


//Components
#include "TextureComponent.h"
#include "LevelComponent.h"
#include "LevelNavigatorComponent.h"

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

	std::shared_ptr<GameObject> level{ new GameObject() };
	const int blockSize{ 64 };
	std::shared_ptr<LevelComponent> levelComponent(new LevelComponent{ 7,blockSize });
	{
		level->AddComponent(levelComponent);
		AddObject(level);

		//Only call this after the object is added to the scene
		level->GetTransform().SetPosition({ 260,0,0 });
		levelComponent->CreateLevel();
	}



	{
		using namespace dae;
		std::shared_ptr<GameObject> qBert{ new GameObject() };
		std::shared_ptr<LevelNavigatorComponent> navigatorComponent(new LevelNavigatorComponent(levelComponent));
		std::shared_ptr<TextureComponent> textureComponent(new TextureComponent{ "QBert.png",{0,0},{blockSize / 2,blockSize / 2} });
		AddObject(qBert);
		qBert->AddComponent(textureComponent);
		qBert->AddComponent(navigatorComponent);
		navigatorComponent->MoveToSquare(1, 1);


		m_SceneData->pInputManager->AddCommand(ControllerButtonData{ ControllerButton::ButtonY,ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::NorthEast), qBert.get()), 0);

		m_SceneData->pInputManager->AddCommand(ControllerButtonData{ ControllerButton::ButtonX,ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::NorthWest), qBert.get()), 0);

		m_SceneData->pInputManager->AddCommand(ControllerButtonData{ ControllerButton::ButtonA,ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::SouthWest), qBert.get()), 0);

		m_SceneData->pInputManager->AddCommand(ControllerButtonData{ ControllerButton::ButtonB,ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::SouthEast), qBert.get()), 0);
	}
}
