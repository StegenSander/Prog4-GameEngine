#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"

#include "GameObject.h"
using namespace dae;

TextureComponent::TextureComponent(const std::string& filename)
{
	SetTexture(filename);
}

TextureComponent::TextureComponent(const std::string& filename, glm::vec2 positionOffset)
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
