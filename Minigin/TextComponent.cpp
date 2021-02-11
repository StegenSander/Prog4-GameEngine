#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "Texture2D.h"

TextComponent::TextComponent(const std::string& text, const std::shared_ptr<dae::Font>& font)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr)
{
}

void TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<dae::Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render()
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_pGameObject->GetTransform().GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x + m_RelativeOffset.x, pos.y + m_RelativeOffset.y);
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetRelativeOffset(const glm::vec2& relativeOffset)
{
	m_RelativeOffset = relativeOffset;
}

void TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}


