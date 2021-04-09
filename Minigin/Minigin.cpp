#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"

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


using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	Time::GetInstance();


	//Serive Locator Initialise
	//ServiceLocator::SetSoundSystem(new SDLSoundSystem(100));
	ServiceLocator::SetSoundSystem(new SDLSoundSystem());
}
/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame()
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Demo");

	std::shared_ptr<GameObject> background{ new GameObject() };
	std::shared_ptr<TextureComponent> backgroundTexture (new TextureComponent{"background.jpg" });
	background->AddComponent(backgroundTexture);
	scene.Add(background);

	std::shared_ptr<GameObject> logo{ new GameObject() };
	std::shared_ptr<TextureComponent> logoTexture (new TextureComponent{"logo.png" });
	logo->AddComponent(logoTexture);
	logo->SetPosition(216, 180);
	scene.Add(logo);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	std::shared_ptr<GameObject> AssignmentText{ new GameObject() };
	std::shared_ptr<TextComponent> textComponent{new TextComponent{ "Programming 4 Assignment", font } };
	AssignmentText->AddComponent(textComponent);
	AssignmentText->SetPosition(80, 20);
	scene.Add(AssignmentText);
	
	
	std::shared_ptr<GameObject> FPSObject{ new GameObject() };

	std::shared_ptr<TextComponent> FPSTextComponent{ new TextComponent{ "0", font }};
	std::shared_ptr<FPSDisplayScript> FPSComponent{ new FPSDisplayScript{ FPSTextComponent } };
	FPSObject->AddComponent(FPSComponent);
	FPSObject->AddComponent(FPSTextComponent);
	FPSTextComponent->SetColor({ 255,100,100 });
	FPSObject->SetPosition(0, 0);
	scene.Add(FPSObject);

	std::shared_ptr<GameObject> p1 = CreatePlayer(0);
	m_Player1 = p1;
	scene.Add(p1);
	std::shared_ptr<GameObject> p2 = CreatePlayer(1);
	m_Player2 = p2;
	scene.Add(p2);

	std::shared_ptr<GameObject> Scoreboard{ new GameObject() };
	std::shared_ptr<PlayerUIComponent> UIComponent{new PlayerUIComponent(p1,p2)};
	Scoreboard->AddComponent(UIComponent);
	scene.Add(Scoreboard);

	std::shared_ptr<GameObject> ui{ new GameObject() };

	std::shared_ptr<UIButtonScript> uiButtonScript{ new UIButtonScript() };
	ui->AddComponent(uiButtonScript);
	scene.Add(ui);
}



std::shared_ptr<dae::GameObject> dae::Minigin::CreatePlayer(int index)
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

	InputManager::GetInstance().AddCommand(ControllerButtonData{ ControllerButton::ButtonA,ButtonState::OnPress }
	, new Command(std::bind(&HealthComponent::DealDamage, QBertHealth, 1), player.get()), index);

	dae::InputManager::GetInstance().AddCommand(ControllerButtonData{ ControllerButton::ButtonB,ButtonState::OnRelease }
	, new Command{ std::bind(&ScoreComponent::ScorePoint,scoreComp,10),player.get() }, index);
	dae::InputManager::GetInstance().AddCommand(ControllerButtonData{ ControllerButton::ButtonX,ButtonState::OnRelease }
	, new Command{ std::bind(&ScoreComponent::ScorePoint,scoreComp,50),player.get() }, index);
	dae::InputManager::GetInstance().AddCommand(ControllerButtonData{ ControllerButton::ButtonY,ButtonState::OnRelease }
	, new Command{ std::bind(&ScoreComponent::ScorePoint,scoreComp,100) ,player.get() }, index);

	return player;
}

void dae::Minigin::Cleanup()
{
	if (ServiceLocator::GetSoundSystem()) delete ServiceLocator::GetSoundSystem();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}
void dae::Minigin::Run()
{
	Initialize();
	InputManager::GetInstance().SetAmountOfControllers(2);

	//example on how to create a input command
	/*InputManager::GetInstance().AddCommand(KeyboardKeyData{ SDL_SCANCODE_B,ButtonState::OnPressAndRelease }
	, new Command(&Commands::Spawn));

	InputManager::GetInstance().AddCommand(ControllerButtonData{ControllerButton::ButtonB,ButtonState::OnPressAndRelease }
	, new Command(&Commands::Spawn));*/

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");


	LoadGame();
	
	ServiceLocator::GetSoundSystem()->PlayEffect("../Data/door1.wav");

	PrintHowToPlay();
	{
		Renderer& renderer = Renderer::GetInstance();
		SceneManager& sceneManager = SceneManager::GetInstance();
		InputManager& input = InputManager::GetInstance();
		Time& time = Time::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			Time::GetInstance().Update();
			const auto currentTime = time.GetLatestTime();
			
			doContinue = input.ProcessInput();

			sceneManager.Update();

			input.RemoveMarkedCommands();
			sceneManager.DestroyMarkedObjects();

			renderer.Render();
			
			auto sleepTime = duration_cast<duration<float>>
				(currentTime + milliseconds(static_cast<int>(time.GetMsPerFrame())) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void dae::Minigin::PrintHowToPlay() const
{
	std::cout << "-----QBERT-----\nHow to play:\n";
	std::cout << "Deal damage to the player: Controller button A\n";
	std::cout << "Score points:\n";
	std::cout << "\tController button B: 10 points\n";
	std::cout << "\tController button X: 50 points\n";
	std::cout << "\tController button Y: 100 points\n";
}
