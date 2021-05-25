#pragma once
#include "BlockComponent.h"

class TextureComponent;
class LevelComponent;
class ColorCubeComponent :
	public BlockComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	ColorCubeComponent(int row, int column, const glm::vec2& standPos, LevelComponent* pLevel, const std::weak_ptr<TextureComponent>& pTexture);
	virtual ~ColorCubeComponent();

	//------COPY CONSTRUCTORS------
	ColorCubeComponent(const ColorCubeComponent&) = delete;
	ColorCubeComponent(ColorCubeComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	ColorCubeComponent operator=(const ColorCubeComponent&) = delete;
	ColorCubeComponent& operator=(ColorCubeComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void BlockTouched(EntityType type) override;
	bool IsCompleted() override;
	void Update() override;
	void Reset() override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	void ColorCube();
	void UnColorCube();
	void UpdateTexture();

	//------PRIVATE VARIABLES------	
	LevelComponent* m_pLevel{};
	std::weak_ptr<TextureComponent> m_pTexture{};

	int m_ColorLevel = 0;
	int m_MaxColorLevel = 1;
	bool m_IsRevertable = true;
};

