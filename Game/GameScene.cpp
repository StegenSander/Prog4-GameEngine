#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "LevelLoader.h"
#include "ExtraMath.h"
#include <SDL_scancode.h>


//Components
#include "TextureComponent.h"
#include "LevelComponent.h"
#include "LevelNavigatorComponent.h"
#include "QBertComponent.h"
#include "HealthComponent.h"
#include "SpawnerComponent.h"
#include "GameControllerComponent.h"
#include "SlickAndSamComponent.h"
#include "UggAndWrongwayComponent.h"
#include "CoilyComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "CoilyPlayerComponent.h"
#include "ButtonComponent.h"

GameScene::GameScene(int levelIndex)
	: Scene("GameScene")
	, m_LevelFilePath{"../Data/level" + std::to_string(levelIndex) + ".bin"}
	, m_LevelIndex{levelIndex}
{
}

void GameScene::Initialise()
{
	using namespace dae;
	
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
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

	//Button MainMenu
	{
		std::shared_ptr<GameObject> button{ new GameObject() };
		std::shared_ptr<TextureComponent> buttonTexture(new TextureComponent{ "Button.png" });
		std::shared_ptr<TextComponent> buttonText(new TextComponent("Back", font));
		std::shared_ptr<ButtonComponent> buttonComp(
			new ButtonComponent({ 0,0 }, { 128,48 }
		, std::bind(&GameScene::LoadMainMenu, this)));
		buttonText->SetRelativeOffset({ 28, 6 });
		button->AddComponent(buttonTexture);
		button->AddComponent(buttonText);
		button->AddComponent(buttonComp);
		button->GetTransform().SetPosition({ 0,420,0 });
		buttonTexture->SetSize({ 128,48 });
		AddObject(button);
	}
	{
		std::shared_ptr<GameObject> controls{ new GameObject() };
		std::shared_ptr<TextureComponent> controlsTexture(new TextureComponent{ "ButtonB.png" });
		controls->GetTransform().SetPosition({ 100,440,0 });
		controlsTexture->SetSize({ 32 ,32 });
		controls->AddComponent(controlsTexture);
		AddObject(controls);
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

		if (m_LastLevelHealth == -1) m_LastLevelHealth = m_QBertData.Lives;
		std::shared_ptr<HealthComponent> healthComp(
				new HealthComponent(m_LastLevelHealth, m_QBertData.Lives, healthTextureComponent, gameControllerComponent));
		m_pHealth = healthComp;

		health->AddComponent(healthTextureComponent);
		health->AddComponent(healthComp);
		AddObject(health);
	}

	//Score
	{
		std::shared_ptr<GameObject> score{ new GameObject() };
		std::shared_ptr<TextComponent> scoreTextComponent(new TextComponent{"0",font});
		scoreTextComponent->SetRelativeOffset({ 0,40 });
		
		std::shared_ptr<ScoreComponent>scoreComp (new ScoreComponent(scoreTextComponent, m_LastLevelScore));
		m_pScore = scoreComp;
		score->AddComponent(scoreTextComponent);
		score->AddComponent(scoreComp);
		AddObject(score);
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
		if (m_GameMode == GameMode::Coop)
		{
			CreateQbert(ExtraMath::PyramidAmountOfBlockUntil(m_LevelData.LevelSize +1, 2), 0);
			CreateQbert(ExtraMath::PyramidAmountOfBlockUntil(m_LevelData.LevelSize +1, m_LevelData.LevelSize), 1);
		}
		else
		{
			CreateQbert(ExtraMath::PyramidAmountOfBlockUntil(3, 2), 0);
		}
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


	m_SceneData->pInputManager->AddCommand(ControllerButtonData(ControllerButton::ButtonB, ButtonState::Down)
		, new Command(std::bind(&GameScene::LoadMainMenu, this), this));
}

std::shared_ptr<dae::GameObject> GameScene::SpawnSlickAndSam() const
{
	//std::cout << "Spawn Slick And Sam called\n";
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
	
	MoveResult result = SandSComponent->FullReset();
	if (!result.DidMove) obj->MarkForDelete();
	return obj;
}
std::shared_ptr<dae::GameObject> GameScene::SpawnUggAndWrongway()
{
	//std::cout << "Spawn Ugg And Wrongway called\n";
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

	MoveResult result = UandWComponent->FullReset();
	if (!result.DidMove) obj->MarkForDelete();

	return obj;
}
std::shared_ptr<dae::GameObject> GameScene::SpawnCoily() const
{
	//std::cout << "Spawn Coily called\n";
	std::shared_ptr<dae::GameObject> obj{ new dae::GameObject };
	std::shared_ptr<LevelNavigatorComponent> levelNavComponent(new LevelNavigatorComponent(m_pLevel));
	int spawnIndexColiy = ExtraMath::PyramidAmountOfBlockUntil(3, 2);

	std::shared_ptr<TextureComponent> textureComponent 
		= std::shared_ptr<TextureComponent>(new TextureComponent{ "Enemies/Coily1.png",{0,0},{m_BlockSize / 2,m_BlockSize / 2} });
	
	obj->AddComponent(levelNavComponent);
	obj->AddComponent(textureComponent);


	if (m_GameMode == GameMode::Versus)
	{
		std::shared_ptr<CoilyPlayerComponent> coilyComponent(
			new CoilyPlayerComponent(levelNavComponent, m_pGameController
				, textureComponent, spawnIndexColiy,1, m_CoilyData.TimeBetweenMoves));
		obj->AddComponent(coilyComponent);
		MoveResult result = coilyComponent->FullReset();
		if (!result.DidMove) obj->MarkForDelete();

		using namespace dae;
		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_I, ButtonState::Down }
		, new Command(std::bind(&CoilyPlayerComponent::Move, coilyComponent.get(), Direction::NorthEast), coilyComponent.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_J, ButtonState::Down }
		, new Command(std::bind(&CoilyPlayerComponent::Move, coilyComponent.get(), Direction::NorthWest), coilyComponent.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_K, ButtonState::Down }
		, new Command(std::bind(&CoilyPlayerComponent::Move, coilyComponent.get(), Direction::SouthWest), coilyComponent.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_L, ButtonState::Down }
		, new Command(std::bind(&CoilyPlayerComponent::Move, coilyComponent.get(), Direction::SouthEast), coilyComponent.get()));
	}
	else
	{
		std::shared_ptr<CoilyComponent> coilyComponent(
			new CoilyComponent(levelNavComponent, m_pGameController
				, textureComponent, spawnIndexColiy, m_CoilyData.TimeBetweenMoves));
		obj->AddComponent(coilyComponent);
		MoveResult result = coilyComponent->FullReset();
		if (!result.DidMove) obj->MarkForDelete();
	}

	return obj;
}

void GameScene::CreateQbert(int spawnIndex, int controlsIndex)
{
	using namespace dae;
	std::shared_ptr<GameObject> qBert{ new GameObject() };
	std::shared_ptr<LevelNavigatorComponent> navigatorComponent(new LevelNavigatorComponent(m_pLevel));
	m_pQbertNavigator = navigatorComponent;
	std::shared_ptr<QBertComponent> qbertComponent(
		new QBertComponent(navigatorComponent, DWORD(controlsIndex), m_pGameController, spawnIndex, m_QBertData.TimeBetweenMoves));
	std::shared_ptr<TextureComponent> textureComponent(new TextureComponent{ "QBert.png",{0,0},{m_BlockSize / 2,m_BlockSize / 2} });
	AddObject(qBert);
	qBert->AddComponent(textureComponent);
	qBert->AddComponent(navigatorComponent);
	qBert->AddComponent(qbertComponent);
	qbertComponent->FullReset();

	if (controlsIndex == 0)
	{
		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_W, ButtonState::Down }
		, new Command(std::bind(&QBertComponent::Move, qbertComponent, Direction::NorthEast), qbertComponent.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_A, ButtonState::Down }
		, new Command(std::bind(&QBertComponent::Move, qbertComponent, Direction::NorthWest), qbertComponent.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_S, ButtonState::Down }
		, new Command(std::bind(&QBertComponent::Move, qbertComponent, Direction::SouthWest), qbertComponent.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_D, ButtonState::Down }
		, new Command(std::bind(&QBertComponent::Move, qbertComponent, Direction::SouthEast), qbertComponent.get()));
	}
	else if (controlsIndex == 1)
	{
		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_I, ButtonState::Down }
		, new Command(std::bind(&QBertComponent::Move, qbertComponent, Direction::NorthEast), qbertComponent.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_J, ButtonState::Down }
		, new Command(std::bind(&QBertComponent::Move, qbertComponent, Direction::NorthWest), qbertComponent.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_K, ButtonState::Down }
		, new Command(std::bind(&QBertComponent::Move, qbertComponent, Direction::SouthWest), qbertComponent.get()));

		m_SceneData->pInputManager->AddCommand(KeyboardKeyData{ SDL_SCANCODE_L, ButtonState::Down }
		, new Command(std::bind(&QBertComponent::Move, qbertComponent, Direction::SouthEast), qbertComponent.get()));
	}
}
void GameScene::SetLevelIndex(int index)
{
	m_LevelIndex = index;
	m_LevelFilePath = std::string{ "../Data/level" + std::to_string(m_LevelIndex) + ".bin" };
}
void GameScene::SafeLastVariables()
{
	if (!m_pHealth.expired())
	{
		m_LastLevelHealth = m_pHealth.lock()->GetHealth();
	}
	if (!m_pScore.expired())
	{
		m_LastLevelScore = m_pScore.lock()->GetScore();
	}
}
void GameScene::LoadNextLevel()
{
	SafeLastVariables();
	int newIndex = ++m_LevelIndex;
	if (newIndex >m_AmountOfLevels || newIndex < 1)
	{
		LoadMainMenu();
	}
	else
	{
		SetLevelIndex(newIndex);
		Reset();
	}
}

void GameScene::LoadMainMenu()
{
	m_LastLevelHealth = -1;
	m_LastLevelScore = 0;
	SetLevelIndex(1);
	dae::SceneManager::GetInstance().SetActiveScene("MainMenuScene");
}

