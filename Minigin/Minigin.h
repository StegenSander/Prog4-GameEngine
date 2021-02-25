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
	private:
		SDL_Window* m_Window{};
		GameObject* m_pPlayer1 = nullptr;
		GameObject* m_pPlayer2 = nullptr;

		GameObject* CreatePlayer(int index);
	};
}