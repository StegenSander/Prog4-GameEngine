#include "MiniginPCH.h"
#include "TestScene.h"

//Components
#include "GameObject.h"

#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSDisplayScript.h"
#include "UIButtonsScript.h"
#include "HealthComponent.h"
#include "PlayerComponent.h"
#include "PlayerUIComponent.h"
#include "ScoreComponent.h"

#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include "LoggerSoundSystem.h"

#include "SubjectComponent.h"
#include "ResourceManager.h"
#include "InputManager.h"


using namespace dae;
TestScene::TestScene()
	: Scene("TestScene")
{
}

void TestScene::Initialise()
{
	std::shared_ptr<GameObject> background{ new GameObject() };
	std::shared_ptr<TextureComponent> backgroundTexture(new TextureComponent{ "background.jpg" });
	background->AddComponent(backgroundTexture);
	AddObject(background);

	std::shared_ptr<GameObject> logo{ new GameObject() };
	std::shared_ptr<TextureComponent> logoTexture(new TextureComponent{ "logo.png" });
	logo->AddComponent(logoTexture);
	logo->SetPosition(216, 180);
	AddObject(logo);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	std::shared_ptr<GameObject> AssignmentText{ new GameObject() };
	std::shared_ptr<TextComponent> textComponent{ new TextComponent{ "Programming 4 Assignment", font } };
	AssignmentText->AddComponent(textComponent);
	AssignmentText->SetPosition(80, 20);
	AddObject(AssignmentText);


	std::shared_ptr<GameObject> FPSObject{ new GameObject() };

	std::shared_ptr<TextComponent> FPSTextComponent{ new TextComponent{ "0", font } };
	std::shared_ptr<FPSDisplayScript> FPSComponent{ new FPSDisplayScript{ FPSTextComponent } };
	FPSObject->AddComponent(FPSComponent);
	FPSObject->AddComponent(FPSTextComponent);
	FPSTextComponent->SetColor({ 255,100,100 });
	FPSObject->SetPosition(0, 0);
	AddObject(FPSObject);

	std::shared_ptr<GameObject> p1 = CreatePlayer(0);
	m_Player1 = p1;
	AddObject(p1);
	std::shared_ptr<GameObject> p2 = CreatePlayer(1);
	m_Player2 = p2;
	AddObject(p2);

	std::shared_ptr<GameObject> Scoreboard{ new GameObject() };
	std::shared_ptr<PlayerUIComponent> UIComponent{ new PlayerUIComponent(p1,p2) };
	Scoreboard->AddComponent(UIComponent);
	AddObject(Scoreboard);

	std::shared_ptr<GameObject> ui{ new GameObject() };

	std::shared_ptr<UIButtonScript> uiButtonScript{ new UIButtonScript() };
	ui->AddComponent(uiButtonScript);
	AddObject(ui);
}

std::shared_ptr<GameObject> TestScene::CreatePlayer(int index)
{
	std::shared_ptr<GameObject> player{ new GameObject() };

	std::shared_ptr<TextureComponent> QBertTexture{ new TextureComponent{ "QBert.png" } };
	player->AddComponent(QBertTexture);

	std::shared_ptr<HealthComponent> QBertHealth{ new HealthComponent(3) };
	player->AddComponent(QBertHealth);

	std::shared_ptr<ScoreComponent> scoreComp{ new ScoreComponent() };
	player->AddComponent(scoreComp);

	std::shared_ptr<PlayerComponent> playerComp{ new PlayerComponent(index) };
	player->AddComponent(playerComp);


	m_SceneData->pInputManager->AddCommand(ControllerButtonData{ ControllerButton::ButtonA,ButtonState::OnPress }
	, new Command(std::bind(&HealthComponent::DealDamage, QBertHealth, 1), player.get()), index);

	m_SceneData->pInputManager->AddCommand(ControllerButtonData{ ControllerButton::ButtonB,ButtonState::OnRelease }
	, new Command{ std::bind(&ScoreComponent::ScorePoint,scoreComp,10),player.get() }, index);
	m_SceneData->pInputManager->AddCommand(ControllerButtonData{ ControllerButton::ButtonX,ButtonState::OnRelease }
	, new Command{ std::bind(&ScoreComponent::ScorePoint,scoreComp,50),player.get() }, index);
	m_SceneData->pInputManager->AddCommand(ControllerButtonData{ ControllerButton::ButtonY,ButtonState::OnRelease }
	, new Command{ std::bind(&ScoreComponent::ScorePoint,scoreComp,100) ,player.get() }, index);

	return player;
}