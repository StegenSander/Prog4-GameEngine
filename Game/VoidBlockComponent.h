#pragma once
#include "BlockComponent.h"

class LevelComponent;
class VoidBlockComponent
	: public BlockComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	VoidBlockComponent(int row, int column, const glm::vec2& blockPos, int blockSize, LevelComponent* pLevel);
	virtual ~VoidBlockComponent() = default;

	//------COPY CONSTRUCTORS------
	VoidBlockComponent(const VoidBlockComponent&) = delete;
	VoidBlockComponent(VoidBlockComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	VoidBlockComponent operator=(const VoidBlockComponent&) = delete;
	VoidBlockComponent& operator=(VoidBlockComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void BlockTouched(const EntityInfo& info) override;

	//------PUBLIC VARIABLES------
};

