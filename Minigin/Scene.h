#pragma once
#include "SceneManager.h"

#include "InputManager.h"
#include "GameObject.h"
struct SceneData
{
	dae::InputManager* pInputManager;
};

namespace dae
{
	class Scene
	{
	public:

		explicit Scene(const std::string& name);

		void AddObject(const std::shared_ptr<GameObject>& object);

		virtual void Initialise() = 0;

		virtual void OnSceneLoad() {};
		virtual void OnSceneUnload() {};
		void Update();
		void Render() const;

		void DestroyMarkedObjects();

		template <typename T>
		std::weak_ptr<T> FindObjectOfType();

		virtual ~Scene();
		
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::string GetName() const { return m_Name; }
		SceneData* GetSceneData() const { return m_SceneData; }

	protected:
		SceneData* m_SceneData;

	private: 
		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};
	};

	template<typename T>
	inline std::weak_ptr<T> Scene::FindObjectOfType()
	{
		for (const auto& obj : m_Objects )
		{
			std::weak_ptr<T> ptr = obj->GetComponent<T>();
			if (!ptr.expired() && ptr.lock().get() != nullptr) return ptr;
		}
		return std::weak_ptr<T>();
	}

}
