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
		//Use this function to clean necessary data
		virtual void OnReset() {}
		void Update();
		void Render() const;
		/// <summary>
		/// Reset will not clean everything
		/// Reset cleans up all GameObject and Components and then calls Initialise again
		/// Some member variables might not get reset
		/// Use OnReset() override to reset these if necessary
		/// </summary>
		void Reset();

		void PostUpdate();

		template <typename T>
		std::weak_ptr<T> FindObjectOfType();
		template <typename T>
		std::vector<std::weak_ptr<T>> FindObjectsOfType();

		virtual ~Scene();
		
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		[[nodiscard]] const std::string& GetName() const { return m_Name; }
		[[nodiscard]] SceneData* GetSceneData() const { return m_SceneData; }

	protected:
		SceneData* m_SceneData;

	private: 
		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};
		bool m_MustReset;
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

	template<typename T>
	inline std::vector<std::weak_ptr<T>> Scene::FindObjectsOfType()
	{
		std::vector<std::weak_ptr<T>> result{};
		for (const auto& obj : m_Objects)
		{
			std::weak_ptr<T> ptr = obj->GetComponent<T>();
			if (!ptr.expired() && ptr.lock().get() != nullptr) result.push_back(ptr);
		}
		return result;
	}

}
