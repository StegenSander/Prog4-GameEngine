#pragma once
#include "RenderComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae {
	class Texture2D;
}
class TextureComponent
	: public RenderComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	TextureComponent(dae::GameObject* pGameObject);
	TextureComponent(dae::GameObject* pGameObject, const std::string& filename);
	TextureComponent(dae::GameObject* pGameObject, const std::string& filename, glm::vec2 positionOffset);
	virtual ~TextureComponent() = default;

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
	void SetPositionOffset(glm::vec2 positionOffset);

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------
	std::shared_ptr<dae::Texture2D> m_Texture {nullptr};
	glm::vec2 m_PositionOffset {0,0};
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};
