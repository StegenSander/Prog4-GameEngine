#pragma once
#include "Scene.h"
#include "DataStructures.h"
namespace dae {
	class GameObject;
}
class MainMenuScene
	: public dae::Scene
{
public:
	MainMenuScene();
	void Initialise() override;
private:
	void LoadSoloGame();
	void LoadCoopGame();
	void LoadVersusGame();
	void LoadGame(GameMode mode);
};

