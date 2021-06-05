#include "MiniginPCH.h"
#include "MainMenuScene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "ButtonComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameScene.h"

MainMenuScene::MainMenuScene()
	: Scene("MainMenuScene")
{
}

void MainMenuScene::Initialise()
{

	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	using namespace dae;
	//Background
	{
		std::shared_ptr<GameObject> background{ new GameObject() };
		std::shared_ptr<TextureComponent> backgroundTexture(new TextureComponent{ "background.jpg" });
		background->AddComponent(backgroundTexture);
		AddObject(background);
	}

	//Controls1
	{
		std::shared_ptr<GameObject> controls{ new GameObject() };
		std::shared_ptr<TextureComponent> controlsTexture(new TextureComponent{ "Controls1.png" });
		controls->GetTransform().SetPosition({35,150,0 });
		controlsTexture->SetSize({ 180 ,236 });
		controls->AddComponent(controlsTexture);
		AddObject(controls);
	}
	//Controls2
	{
		std::shared_ptr<GameObject> controls{ new GameObject() };
		std::shared_ptr<TextureComponent> controlsTexture(new TextureComponent{ "Controls2.png" });
		controls->GetTransform().SetPosition({ 420,150,0 });
		controlsTexture->SetSize({ 180 ,236 });
		controls->AddComponent(controlsTexture);
		AddObject(controls);
	}


	//Logo
	{
		std::shared_ptr<GameObject> logo{ new GameObject() };
		std::shared_ptr<TextureComponent> logoTexture(new TextureComponent{ "QbertName.png" });
		logo->AddComponent(logoTexture);
		logo->GetTransform().SetPosition({ 170,20,0 });
		logoTexture->SetSize({ 300,50 });
		AddObject(logo);
	}

	//Button Solo
	{
		std::shared_ptr<GameObject> button{ new GameObject() };
		std::shared_ptr<TextureComponent> buttonTexture(new TextureComponent{ "Button.png" });
		std::shared_ptr<TextComponent> buttonText(new TextComponent("Solo", font));
		std::shared_ptr<ButtonComponent> buttonComp(
			new ButtonComponent({ 0,0 }, { 128,48 }
		, std::bind(&MainMenuScene::LoadSoloGame, this)));
		buttonText->SetRelativeOffset({ 28, 6 });
		button->AddComponent(buttonTexture);
		button->AddComponent(buttonText);
		button->AddComponent(buttonComp);
		button->GetTransform().SetPosition({ 250,200,0 });
		buttonTexture->SetSize({ 128,48 });
		AddObject(button);
	}

	//Button Coop
	{
		std::shared_ptr<GameObject> button{ new GameObject() };
		std::shared_ptr<TextureComponent> buttonTexture(new TextureComponent{ "Button.png" });
		std::shared_ptr<TextComponent> buttonText(new TextComponent("Co-op", font));
		std::shared_ptr<ButtonComponent> buttonComp(
			new ButtonComponent({ 0,0 }, { 128,48 }
		, std::bind(&MainMenuScene::LoadCoopGame, this)));
		buttonText->SetRelativeOffset({ 16, 6 });
		button->AddComponent(buttonTexture);
		button->AddComponent(buttonText);
		button->AddComponent(buttonComp);
		button->GetTransform().SetPosition({ 250,250,0 });
		buttonTexture->SetSize({ 128,48 });
		AddObject(button);
	}

	//Button Versus
	{
		std::shared_ptr<GameObject> button{ new GameObject() };
		std::shared_ptr<TextureComponent> buttonTexture(new TextureComponent{ "Button.png" });
		std::shared_ptr<TextComponent> buttonText(new TextComponent("Versus", font));
		std::shared_ptr<ButtonComponent> buttonComp(
			new ButtonComponent({ 0,0 }, { 128,48 }
		, std::bind(&MainMenuScene::LoadVersusGame, this)));
		buttonText->SetRelativeOffset({ 10, 6 });
		button->AddComponent(buttonTexture);
		button->AddComponent(buttonText);
		button->AddComponent(buttonComp);
		button->GetTransform().SetPosition({ 250,300,0 });
		buttonTexture->SetSize({ 128,48 });
		AddObject(button);
	}
	//Controls3
	{
		{
			std::shared_ptr<GameObject> controls{ new GameObject() };
			std::shared_ptr<TextureComponent> controlsTexture(new TextureComponent{ "ButtonA.png" });
			controls->GetTransform().SetPosition({ 360,220,0 });
			controlsTexture->SetSize({ 32 ,32 });
			controls->AddComponent(controlsTexture);
			AddObject(controls);
		}
		{
			std::shared_ptr<GameObject> controls{ new GameObject() };
			std::shared_ptr<TextureComponent> controlsTexture(new TextureComponent{ "ButtonB.png" });
			controls->GetTransform().SetPosition({ 360,270,0 });
			controlsTexture->SetSize({ 32 ,32 });
			controls->AddComponent(controlsTexture);
			AddObject(controls);
		}
		{
			std::shared_ptr<GameObject> controls{ new GameObject() };
			std::shared_ptr<TextureComponent> controlsTexture(new TextureComponent{ "ButtonY.png" });
			controls->GetTransform().SetPosition({ 360,320,0 });
			controlsTexture->SetSize({ 32 ,32 });
			controls->AddComponent(controlsTexture);
			AddObject(controls);
		}
	}
	m_SceneData->pInputManager->AddCommand(ControllerButtonData(ControllerButton::ButtonA,ButtonState::Down)
		, new Command(std::bind(&MainMenuScene::LoadSoloGame, this), this));
	m_SceneData->pInputManager->AddCommand(ControllerButtonData(ControllerButton::ButtonB, ButtonState::Down)
		, new Command(std::bind(&MainMenuScene::LoadCoopGame, this), this));
	m_SceneData->pInputManager->AddCommand(ControllerButtonData(ControllerButton::ButtonY, ButtonState::Down)
		, new Command(std::bind(&MainMenuScene::LoadVersusGame, this), this));
}

void MainMenuScene::LoadSoloGame()
{
	LoadGame(GameMode::Solo);
}

void MainMenuScene::LoadCoopGame()
{
	LoadGame(GameMode::Coop);
}

void MainMenuScene::LoadVersusGame()
{
	LoadGame(GameMode::Versus);
}

void MainMenuScene::LoadGame(GameMode mode)
{
	dae::SceneManager::GetInstance().SetActiveScene("GameScene");
	dae::Scene* scene = dae::SceneManager::GetInstance().GetActiveScene();
	GameScene* gameScene = dynamic_cast<GameScene*>(scene);
	if (gameScene)
	{
		gameScene->SetGameMode(mode);
		gameScene->Reset();
	}
}
