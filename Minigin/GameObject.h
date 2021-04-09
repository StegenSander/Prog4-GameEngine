#pragma once
#include "Transform.h"
#include "Destroyable.h"

class BaseComponent;

namespace dae
{
	class GameObject
		: public Destroyable
	{
	public:
		GameObject();
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;

		void SetPosition(float x, float y);

		Transform GetTransform() const { return m_Transform; };

		void AddComponent(const std::shared_ptr<BaseComponent>& pComponent);
		template <typename T>
		std::weak_ptr<T> GetComponent();

		void RemoveComponents();
	private:
		Transform m_Transform;

		std::vector<std::shared_ptr<BaseComponent>> m_Components;

	};

	template<typename T>
	inline std::weak_ptr<T> GameObject::GetComponent()
	{
		for (std::shared_ptr<BaseComponent> pBase : m_Components)
		{
			if (std::dynamic_pointer_cast<T>(pBase))
			{
				return std::dynamic_pointer_cast<T> (pBase);
			}
		}

		return std::shared_ptr<T>(nullptr);
	}
}