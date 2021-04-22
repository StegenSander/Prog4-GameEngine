#pragma once
struct SDL_Window;
class ScoreboardComponent;
namespace dae
{
	class GameObject;
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame();
		void Cleanup();
		void Run();

		void PrintHowToPlay() const;
	private:
		SDL_Window* m_Window{};
	};
}