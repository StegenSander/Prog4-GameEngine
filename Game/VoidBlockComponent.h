#pragma once
#include "BlockComponent.h"

class LevelComponent;
class VoidBlockComponent
	: public BlockComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	VoidBlockComponent(int row, int column, const glm::vec2& standPos, LevelComponent* pLevel);
	virtual ~VoidBlockComponent();

	//------COPY CONSTRUCTORS------
	VoidBlockComponent(const VoidBlockComponent&) = delete;
	VoidBlockComponent(VoidBlockComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	VoidBlockComponent operator=(const VoidBlockComponent&) = delete;
	VoidBlockComponent& operator=(VoidBlockComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void BlockTouched(EntityType type) override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------
	LevelComponent* m_pLevel{};
};

