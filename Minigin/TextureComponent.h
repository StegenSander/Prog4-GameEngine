#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae {
	class Texture2D;
}
class TextureComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	TextureComponent() = default;
	TextureComponent(const std::string& filename);
	TextureComponent(const std::string& filename, const glm::vec2& positionOffset);
	TextureComponent(const std::string& filename, const glm::vec2& positionOffset, const glm::vec2& size);
	virtual ~TextureComponent() {
		std::cout << "Texture Component deleted\n";
	}
	;;

	//------COPY CONSTRUCTORS------
	TextureComponent(const TextureComponent&) = delete;
	TextureComponent(TextureComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	TextureComponent operator=(const TextureComponent&) = delete;
	TextureComponent& operator=(TextureComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override {};
	void Render() override;
	void SetTexture(const std::string& filename);
	void SetSize(const glm::vec2& size) { m_Size = size; }
	void SetSizeToTextureSize();
	void SetPositionOffset(const glm::vec2& positionOffset);

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------
	std::shared_ptr<dae::Texture2D> m_Texture {nullptr};
	glm::vec2 m_PositionOffset {0,0};
	glm::vec2 m_Size{ 0,0 };
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};
