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

		void Update();
		void Render();
		void SetActiveScene(const std::string& name);
		dae::Scene& GetActiveScene();

		void RegisterScene(const std::shared_ptr<Scene>& scene);

		void DestroyMarkedObjects();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::shared_ptr<Scene> m_ActiveScene;
		std::map<std::string, std::shared_ptr<Scene>> m_SceneMap;
	};
}
