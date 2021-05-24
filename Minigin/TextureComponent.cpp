#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Transform.h"

#include "Texture2D.h"
#include <SDL.h>
using namespace dae;

TextureComponent::TextureComponent(const std::string& filename)
	:TextureComponent{ filename, { 0,0 } }
{
}

TextureComponent::TextureComponent(const std::string& filename, const glm::vec2& positionOffset)
{
	SetTexture(filename);
	SetPositionOffset(positionOffset);
	SetSizeToTextureSize();
}

TextureComponent::TextureComponent(const std::string& filename, const glm::vec2& positionOffset, const glm::vec2& size)
	: m_Size{size}
{
	SetTexture(filename);
	SetPositionOffset(positionOffset);
}

void TextureComponent::Render()
{
	if (m_Texture)
	{
		const glm::vec3 pos = m_pGameObject->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x + m_PositionOffset.x, pos.y + m_PositionOffset.y,m_Size.x,m_Size.y);
	}
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::SetSizeToTextureSize()
{
	int x, y;
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &x, &y);
	m_Size.x = float(x);
	m_Size.y = float(y);
}

void TextureComponent::SetPositionOffset(const glm::vec2& positionOffset)
{
	m_PositionOffset = positionOffset;
}
