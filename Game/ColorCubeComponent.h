#pragma once
#include "BlockComponent.h"

enum class ColorChangeBehaviour
{
	SingleTouch,
	DoubleTouch,
	SingleRevertable,
};

class ColorCubeComponent :
	public BlockComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	ColorCubeComponent();
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
};

