#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "GameTime.h"

#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSDisplayScript.h"
#include "UIButtonsScript.h"
#include "PlayerComponent.h"
#include "PlayerUIComponent.h"

#include "ServiceLocator.h"
#include "SDLSoundSystem.h"
#include "LoggerSoundSystem.h"

#include "SubjectComponent.h"

#include "TestScene.h"


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
	GameTime::GetInstance();


	//Serive Locator Initialise
	//ServiceLocator::SetSoundSystem(new SDLSoundSystem(100));
	ServiceLocator::SetSoundSystem(new SDLSoundSystem());


	ResourceManager::GetInstance().Init("../Data/");
}

void dae::Minigin::LoadGame()
{
	SceneManager::GetInstance().Initialise();
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

	//example on how to create a input command
	/*InputManager::GetInstance().AddCommand(KeyboardKeyData{ SDL_SCANCODE_B,ButtonState::OnPressAndRelease }
	, new Command(&Commands::Spawn));

	InputManager::GetInstance().AddCommand(ControllerButtonData{ControllerButton::ButtonB,ButtonState::OnPressAndRelease }
	, new Command(&Commands::Spawn));*/

	// tell the resource manager where he can find the game data


	LoadGame();
	
	//ServiceLocator::GetSoundSystem()->PlayEffect("../Data/door1.wav");

	PrintHowToPlay();
	{
		Renderer& renderer = Renderer::GetInstance();
		SceneManager& sceneManager = SceneManager::GetInstance();
		GameTime& time = GameTime::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			SceneData* sceneData = sceneManager.GetActiveScene().GetSceneData();
			GameTime::GetInstance().Update();
			const auto currentTime = time.GetLatestTime();
			
			doContinue = sceneData->pInputManager->ProcessInput();

			sceneManager.Update();

			sceneData->pInputManager->RemoveMarkedCommands();
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
