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

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
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
	
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Demo");

	GameObject* background = new GameObject();
	TextureComponent* backgroundTexture = new TextureComponent{"background.jpg" };
	background->AddComponent(backgroundTexture);
	scene.Add(background);

	GameObject* logo = new GameObject();
	TextureComponent* logoTexture = new TextureComponent{"logo.png" };
	logo->AddComponent(logoTexture);
	logo->SetPosition(216, 180);
	scene.Add(logo);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	GameObject* AssignmentText = new GameObject();
	auto textComponent = new TextComponent{ "Programming 4 Assignment", font };
	AssignmentText->AddComponent(textComponent);
	AssignmentText->SetPosition(80, 20);
	scene.Add(AssignmentText);
	
	GameObject* FPSObject = new GameObject();
	auto FPSTextComponent = new TextComponent{ "0", font };
	auto FPSComponent = new FPSDisplayScript{ FPSTextComponent };
	FPSObject->AddComponent(FPSComponent);
	FPSObject->AddComponent(FPSTextComponent);
	FPSTextComponent->SetColor({ 255,100,100 });
	FPSObject->SetPosition(0, 0);
	scene.Add(FPSObject);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();
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
			renderer.Render();

			sceneManager.HandleEndOfFrame();
			
			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(static_cast<int>(time.GetMsPerFrame())) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
