#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"

#include "GameObject.h"
using namespace dae;

TextureComponent::TextureComponent(GameObject* pGameObject)
	: RenderComponent(pGameObject)
{
}

TextureComponent::TextureComponent(GameObject* pGameObject, const std::string& filename)
	: RenderComponent(pGameObject)
{
	SetTexture(filename);
}

TextureComponent::TextureComponent(GameObject* pGameObject, const std::string& filename, glm::vec2 positionOffset)
	: RenderComponent(pGameObject)
{
	SetTexture(filename);
	SetPositionOffset(positionOffset);
}

void TextureComponent::Render()
{
	if (m_Texture)
	{
		const glm::vec3 pos = m_pGameObject->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x + m_PositionOffset.x, pos.y + m_PositionOffset.y);
	}
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::SetPositionOffset(glm::vec2 positionOffset)
{
	m_PositionOffset = positionOffset;
}
