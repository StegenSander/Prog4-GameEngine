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
#include "ExtraMath.h"
#include "SpawnerComponent.h"
#include "GameControllerComponent.h"
#include "LevelNavigatorComponent.h"
#include "SlickAndSamComponent.h"
#include "UggAndWrongwayComponent.h"
#include "BlockComponent.h"
#include "CoilyComponent.h"
#include "LevelLoader.h"

GameScene::GameScene(const std::string& filePath)
	: Scene("GameScene")
	, m_LevelFilePath{filePath}
{
}

void GameScene::Initialise()
{
	using namespace dae;
	std::cout << "GameScene Initialised\n";

	//LoadLevel
	LevelLoader::LoadLevel(m_LevelFilePath,m_GameRules, m_LevelData, m_QBertData
		, m_SlickAndSameData, m_UggAndWrongwayData, m_CoilyData);

	//Background
	{
		std::shared_ptr<GameObject> background{ new GameObject() };
		std::shared_ptr<TextureComponent> backgroundTexture(new TextureComponent{ "background.jpg" });
		background->AddComponent(backgroundTexture);
		AddObject(background);
	}

	//Game Controller
	std::shared_ptr<GameObject> gameController{ new GameObject() };
	std::shared_ptr<GameControllerComponent> gameControllerComponent(new GameControllerComponent{});
	m_pGameController = gameControllerComponent;
	gameController->AddComponent(gameControllerComponent);
	AddObject(gameController);

	//Health
	{
		std::shared_ptr<GameObject> health{ new GameObject() };
		std::shared_ptr<TextureComponent> healthTextureComponent(new TextureComponent{ "Health/Health_3.png" });
		std::shared_ptr<HealthComponent> healthComponent(
			new HealthComponent(m_QBertData.Lives, healthTextureComponent, gameControllerComponent));
		health->AddComponent(healthTextureComponent);
		health->AddComponent(healthComponent);
		AddObject(health);
	}

	//Level
	std::shared_ptr<GameObject> level{ new GameObject() };
	std::shared_ptr<LevelComponent> levelComponent(
		new LevelComponent{ m_LevelData.LevelSize,m_BlockSize,m_LevelData.RowOfDiscs
		,gameControllerComponent,m_GameRules.AmountOfColorChanges,m_GameRules.Revertible });
	m_pLevel = levelComponent;
	{
		level->AddComponent(levelComponent);
		AddObject(level);

		//Only call this after the object is added to the scene
		level->GetTransform().SetPosition(m_LevelData.LevelPosition);
		levelComponent->CreateLevel();
	}


	//QBert
	{
		using namespace dae;
		std::shared_ptr<GameObject> qBert{ new GameObject() };
		std::shared_ptr<LevelNavigatorComponent> navigatorComponent(new LevelNavigatorComponent(levelComponent));
		m_pQbertNavigator = navigatorComponent;
		int spawnIndexQBert = ExtraMath::PyramidAmountOfBlockUntil(3, 2);
		std::shared_ptr<QBertComponent> qbertComponent(
			new QBertComponent(navigatorComponent,0, gameControllerComponent,spawnIndexQBert,m_QBertData.TimeBetweenMoves));
		std::shared_ptr<TextureComponent> textureComponent(new TextureComponent{ "QBert.png",{0,0},{m_BlockSize / 2,m_BlockSize / 2} });
		AddObject(qBert);
		qBert->AddComponent(textureComponent);
		qBert->AddComponent(navigatorComponent);
		qBert->AddComponent(qbertComponent);
		qbertComponent->Reset();

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_W, ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::NorthEast, qbertComponent.get()), qBert.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_A, ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::NorthWest, qbertComponent.get()), qBert.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_S, ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::SouthWest, qbertComponent.get()), qBert.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_D, ButtonState::OnPress }
		, new Command(std::bind(&LevelNavigatorComponent::Move, navigatorComponent, Direction::SouthEast, qbertComponent.get()), qBert.get()));
	}

	//Spawners
	{
		std::shared_ptr<GameObject> spawner{ new GameObject() };

		//SlickAndSamSpawner
		{
			std::function<std::shared_ptr<dae::GameObject>()> spawnFunction = std::bind(&GameScene::SpawnSlickAndSam, this);
			std::shared_ptr<SpawnerComponent> spawnerComponent(
				new SpawnerComponent(spawnFunction, m_SlickAndSameData.MaxEntitiesAlive
					, m_SlickAndSameData.MinSpawnDuration, m_SlickAndSameData.MaxSpawnDuration));
			spawner->AddComponent(spawnerComponent);
			AddObject(spawner);
		}
		//UggAndWrongwaySpawner
		{
			std::function<std::shared_ptr<dae::GameObject>()> spawnFunction = std::bind(&GameScene::SpawnUggAndWrongway, this);
			std::shared_ptr<SpawnerComponent> spawnerComponent(
				new SpawnerComponent(spawnFunction, m_UggAndWrongwayData.MaxEntitiesAlive
					, m_UggAndWrongwayData.MinSpawnDuration, m_UggAndWrongwayData.MaxSpawnDuration));
			spawner->AddComponent(spawnerComponent);
			AddObject(spawner);
		}
		//CoilySpawner
		{
			std::function<std::shared_ptr<dae::GameObject>()> spawnFunction = std::bind(&GameScene::SpawnCoily, this);
			std::shared_ptr<SpawnerComponent> spawnerComponent(
				new SpawnerComponent(spawnFunction, m_CoilyData.MaxEntitiesAlive
					, m_CoilyData.MinSpawnDuration, m_CoilyData.MaxSpawnDuration));
			spawner->AddComponent(spawnerComponent);
			AddObject(spawner);
		}
	}
}

std::shared_ptr<dae::GameObject> GameScene::SpawnSlickAndSam()
{
	std::cout << "Spawn Slick And Sam called\n";
	std::shared_ptr<dae::GameObject> obj{ new dae::GameObject };
	std::shared_ptr<LevelNavigatorComponent> levelNavComponent(new LevelNavigatorComponent(m_pLevel));
	int spawnOffset = rand() % 2;
	int spawnIndexSandS = ExtraMath::PyramidAmountOfBlockUntil(4, 2 + spawnOffset);
	std::shared_ptr<SlickAndSamComponent> SandSComponent(
		new SlickAndSamComponent(levelNavComponent,m_pGameController, spawnIndexSandS, m_SlickAndSameData.TimeBetweenMoves));


	std::shared_ptr<TextureComponent> textureComponent;
	if (spawnOffset)
	textureComponent = std::shared_ptr<TextureComponent>(new TextureComponent{ "Enemies/Sam.png",{0,0},{m_BlockSize / 2,m_BlockSize / 2} });
	else
	textureComponent = std::shared_ptr<TextureComponent>(new TextureComponent{ "Enemies/Slick.png",{0,0},{m_BlockSize / 2,m_BlockSize / 2} });
	obj->AddComponent(levelNavComponent);
	obj->AddComponent(SandSComponent);
	obj->AddComponent(textureComponent);
	
	MoveResult result = SandSComponent->Reset();
	if (!result.DidMove) obj->MarkForDelete();
	return obj;
}

std::shared_ptr<dae::GameObject> GameScene::SpawnUggAndWrongway()
{
	std::cout << "Spawn Ugg And Wrongway called\n";
	std::shared_ptr<dae::GameObject> obj{ new dae::GameObject };

	std::shared_ptr<LevelNavigatorComponent> levelNavComponent{};
	std::shared_ptr<UggAndWrongwayComponent> UandWComponent{};
	std::shared_ptr<TextureComponent> textureComponent{};
	const int pyramidSize = m_pLevel.lock()->AmountOfRows();
	if (m_IsUggLastSpawned) //ugg = right one
	{
		levelNavComponent = std::shared_ptr<LevelNavigatorComponent>(
			new LevelNavigatorComponent(m_pLevel, BlockSide::Left));
		int spawnIndexUandW = ExtraMath::PyramidAmountOfBlockUntil(pyramidSize -1, 2);
		UandWComponent= std::shared_ptr<UggAndWrongwayComponent>(
			new UggAndWrongwayComponent(levelNavComponent, m_pGameController, spawnIndexUandW, true,m_UggAndWrongwayData.TimeBetweenMoves));
		textureComponent = std::shared_ptr<TextureComponent>(
			new TextureComponent{ "Enemies/Wrongway.png",{0,0},{m_BlockSize / 2,m_BlockSize / 2} });
		m_IsUggLastSpawned = false;
	}
	else
	{
		levelNavComponent = std::shared_ptr<LevelNavigatorComponent>(
			new LevelNavigatorComponent(m_pLevel, BlockSide::Right));
		int spawnIndexUandW = ExtraMath::PyramidAmountOfBlockUntil(pyramidSize -1, pyramidSize -2);
		UandWComponent = std::shared_ptr<UggAndWrongwayComponent>(
			new UggAndWrongwayComponent(levelNavComponent, m_pGameController, spawnIndexUandW, false, m_UggAndWrongwayData.TimeBetweenMoves));
		textureComponent = std::shared_ptr<TextureComponent>(
			new TextureComponent{ "Enemies/Ugg.png",{0,0},{m_BlockSize / 2,m_BlockSize / 2} });
		m_IsUggLastSpawned = true;
	}
	obj->AddComponent(levelNavComponent);
	obj->AddComponent(UandWComponent);
	obj->AddComponent(textureComponent);

	MoveResult result = UandWComponent->Reset();
	if (!result.DidMove) obj->MarkForDelete();

	return obj;
}

std::shared_ptr<dae::GameObject> GameScene::SpawnCoily()
{
	std::cout << "Spawn Coily called\n";
	std::shared_ptr<dae::GameObject> obj{ new dae::GameObject };
	std::shared_ptr<LevelNavigatorComponent> levelNavComponent(new LevelNavigatorComponent(m_pLevel));
	int spawnIndexColiy = ExtraMath::PyramidAmountOfBlockUntil(3, 2);

	std::shared_ptr<TextureComponent> textureComponent 
		= std::shared_ptr<TextureComponent>(new TextureComponent{ "Enemies/Coily1.png",{0,0},{m_BlockSize / 2,m_BlockSize / 2} });
	std::shared_ptr<CoilyComponent> coilyComponent(
		new CoilyComponent(levelNavComponent, m_pQbertNavigator, m_pGameController
			,textureComponent, spawnIndexColiy,m_CoilyData.TimeBetweenMoves));
	obj->AddComponent(levelNavComponent);
	obj->AddComponent(coilyComponent);
	obj->AddComponent(textureComponent);

	MoveResult result = coilyComponent->Reset();
	if (!result.DidMove) obj->MarkForDelete();

	return obj;
}
