#pragma once
#include "Transform.h"
#include "SceneObject.h"

class BaseComponent;
class RenderComponent;

namespace dae
{
	class Texture2D;
	class GameObject
	{
	public:
		GameObject() = default;
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;

		void SetPosition(float x, float y);

		Transform GetTransform() const { return m_Transform; };

		void AddComponent(BaseComponent* pComponent);

		void Delete() { m_IsMarkedForDelete = true; };
		bool IsMarkedForDelete() const { return m_IsMarkedForDelete; } ;
		void RemoveComponents();
	private:
		Transform m_Transform;

		std::vector<BaseComponent*> m_Components;
		std::vector<RenderComponent*> m_RenderComponents;

		bool m_IsMarkedForDelete = false;

	};
}