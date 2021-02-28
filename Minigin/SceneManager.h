#pragma once
#include "Singleton.h"
#include <map>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetScene(const std::string& name);

		void Update();
		void Render();
		void SetActiveScene(const std::shared_ptr<Scene>& activeScene);

		void DestroyMarkedObjects();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::shared_ptr<Scene> m_ActiveScene;
		std::map<std::string, std::shared_ptr<Scene>> m_SceneMap;
	};
}
