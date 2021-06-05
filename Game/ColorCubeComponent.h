#pragma once
#include "BlockComponent.h"

class TextureComponent;
class LevelComponent;
class ColorCubeComponent :
	public BlockComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	ColorCubeComponent(int row, int column, const glm::vec2& blockPos, int blockSize
		, LevelComponent* pLevel, const std::weak_ptr<TextureComponent>& pTexture
		, int maxColorLevel, bool revertible);
	virtual ~ColorCubeComponent();

	//------COPY CONSTRUCTORS------
	ColorCubeComponent(const ColorCubeComponent&) = delete;
	ColorCubeComponent(ColorCubeComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	ColorCubeComponent operator=(const ColorCubeComponent&) = delete;
	ColorCubeComponent& operator=(ColorCubeComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void BlockTouched(const EntityInfo& info) override;
	bool IsCompleted() override;
	void Update() override;
	void FullReset() override;

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
	std::weak_ptr<TextureComponent> m_pTexture{};

	int m_ColorLevel = 0;
	int m_MaxColorLevel = 2;
	bool m_IsRevertable = false;
};

