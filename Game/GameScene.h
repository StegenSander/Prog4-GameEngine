#pragma once
#include "Scene.h"
namespace dae {
	class GameObject;
}

class LevelComponent;
class GameControllerComponent;
class GameScene : public dae::Scene
{
public:
	GameScene();
	void Initialise() override;

	std::shared_ptr<dae::GameObject> SpawnSlickAndSam();
	std::shared_ptr<dae::GameObject> SpawnUggAndWrongway();
private:
	std::weak_ptr<LevelComponent> m_pLevel;
	std::weak_ptr<GameControllerComponent> m_pGameController;
	const int m_BlockSize = 64;
	const int m_PyramidSize = 7;
	bool m_IsUggLastSpawned = false;
};

