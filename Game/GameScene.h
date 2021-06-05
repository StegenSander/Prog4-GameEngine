#pragma once
#include "Scene.h"
#include "DataStructures.h"
namespace dae {
	class GameObject;
}

class LevelComponent;
class GameControllerComponent;
class LevelNavigatorComponent;
class HealthComponent;
class ScoreComponent;
class GameScene : public dae::Scene
{
public:
	GameScene(int levelIndex);
	void Initialise() override;

	std::shared_ptr<dae::GameObject> SpawnSlickAndSam();
	std::shared_ptr<dae::GameObject> SpawnUggAndWrongway();
	std::shared_ptr<dae::GameObject> SpawnCoily();
	void LoadNextLevel();
	void LoadMainMenu();
	void SetGameMode(GameMode gameMode) { m_GameMode = gameMode; }
private:
	//Functions
	void CreateQbert(int spawnIndex, int controlsIndex);
	void SetLevelIndex(int index);
	void SafeLastVariables();
	//Variables
	//Read Variables
	GameRules m_GameRules{};
	LevelData m_LevelData{};
	QBertData m_QBertData{};
	EntityData m_SlickAndSameData{};
	EntityData m_UggAndWrongwayData{};
	EntityData m_CoilyData{};

	std::string m_LevelFilePath;

	//Current Level Variables
	std::weak_ptr<HealthComponent> m_pHealth;
	std::weak_ptr<ScoreComponent> m_pScore;
	std::weak_ptr<LevelComponent> m_pLevel;
	std::weak_ptr<LevelNavigatorComponent> m_pQbertNavigator;
	std::weak_ptr<GameControllerComponent> m_pGameController;
	int m_LastLevelHealth = -1;
	int m_LastLevelScore = 0;

	//Others
	GameMode m_GameMode = GameMode::Solo;
	const int m_BlockSize = 64;
	int m_LevelIndex;
	bool m_IsUggLastSpawned = false;
	const static int m_AmountOfLevels = 3;
};

