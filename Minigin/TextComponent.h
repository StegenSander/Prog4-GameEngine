#pragma once
#include "RenderComponent.h"
#include "Transform.h"

#include <SDL_pixels.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	class Font;
	class Texture2D;
}
class TextComponent
	: public RenderComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	TextComponent(const std::string& text, const std::shared_ptr<dae::Font>& font);
	virtual ~TextComponent() = default;

	//------COPY CONSTRUCTORS------
	TextComponent(const TextComponent&) = delete;
	TextComponent(TextComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	TextComponent operator=(const TextComponent&) = delete;
	TextComponent& operator=(TextComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;
	void Render() override;


	void SetText(const std::string& text);
	void SetRelativeOffset(const glm::vec2& relativeOffset);
	void SetColor(const SDL_Color& color);


	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------

	bool m_NeedsUpdate;
	std::string m_Text;
	glm::vec2 m_RelativeOffset;
	std::shared_ptr<dae::Font> m_Font;
	std::shared_ptr<dae::Texture2D> m_Texture;
	SDL_Color m_Color = { 255,255,255 };
};

