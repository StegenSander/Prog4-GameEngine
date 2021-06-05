#pragma once
#include "Singleton.h"
#include <map>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& GetScene(const std::string& name);

		void Initialise();
		void Update();
		void Render() const;
		bool SetActiveScene(const std::string& name);
		dae::Scene* GetActiveScene() const;

		void RegisterScene(const std::shared_ptr<Scene>& scene);

		void PostUpdate();
	private:
		struct ReplaceSceneData {
			std::string name;
			std::shared_ptr<Scene> newScene;
		};
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::shared_ptr<Scene> m_ActiveScene;
		std::map<std::string, std::shared_ptr<Scene>> m_SceneMap;
		bool m_IsInitialized{ false };
	};
}
