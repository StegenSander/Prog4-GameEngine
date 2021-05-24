#pragma once
#include "BlockComponent.h"

enum class ColorChangeBehaviour
{
	SingleTouch,
	DoubleTouch,
	SingleRevertable,
};

class TextureComponent;
class LevelComponent;
class ColorCubeComponent :
	public BlockComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	ColorCubeComponent(const std::weak_ptr<LevelComponent>& pLevel);
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
	void Render() override;
	void Update() override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------
	void ColorCube();
	void UnColorCube();

	//------PRIVATE VARIABLES------	
	std::weak_ptr<LevelComponent> m_pLevel{};
	std::weak_ptr<TextureComponent> m_pTexture{};
};

