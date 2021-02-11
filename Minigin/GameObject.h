#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
namespace dae
{
	class Texture2D;
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;
		
		void SetPosition(float x, float y);

		Transform GetTransform() const { return m_Transform; };

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	
	private:
		Transform m_Transform;

		std::vector<BaseComponent*> m_Components;
		std::vector<RenderComponent*> m_RenderComponents;

		void AddComponent(BaseComponent* pComponent);
		void AddRenderComponent(RenderComponent* pRenderComponent);

		friend void BaseComponent::PushComponentToGameObject();
		friend void RenderComponent::PushRenderComponentToGameObject();

	};
}