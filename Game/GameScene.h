#pragma once
#include "Scene.h"
#include "DataStructures.h"
namespace dae {
	class GameObject;
}

class LevelComponent;
class GameControllerComponent;
class LevelNavigatorComponent;
class GameScene : public dae::Scene
{
public:
	GameScene(const std::string& filePath);
	void Initialise() override;

	std::shared_ptr<dae::GameObject> SpawnSlickAndSam();
	std::shared_ptr<dae::GameObject> SpawnUggAndWrongway();
	std::shared_ptr<dae::GameObject> SpawnCoily();
private:
	GameRules m_GameRules{};
	LevelData m_LevelData{};
	QBertData m_QBertData{};
	EntityData m_SlickAndSameData{};
	EntityData m_UggAndWrongwayData{};
	EntityData m_CoilyData{};

	std::string m_LevelFilePath;

	std::weak_ptr<LevelComponent> m_pLevel;
	std::weak_ptr<LevelNavigatorComponent> m_pQbertNavigator;
	std::weak_ptr<GameControllerComponent> m_pGameController;
	const int m_BlockSize = 64;
	bool m_IsUggLastSpawned = false;
};

