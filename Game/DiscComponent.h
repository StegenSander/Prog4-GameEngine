#pragma once
#include "BlockComponent.h"

class DiscComponent
	: public BlockComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	DiscComponent(int row, int column, const glm::vec2& blockPos, int blockSize, LevelComponent* pLevel);
	virtual ~DiscComponent() = default;

	//------COPY CONSTRUCTORS------
	DiscComponent(const DiscComponent&) = delete;
	DiscComponent(DiscComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	DiscComponent operator=(const DiscComponent&) = delete;
	DiscComponent& operator=(DiscComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void BlockTouched(const EntityInfo& info) override;
};
