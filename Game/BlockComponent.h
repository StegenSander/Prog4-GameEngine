#pragma once
#include "BaseComponent.h"

enum class BlockSide
{
	Top,
	Left,
	Right,
};

enum class EntityType;
struct EntityInfo;
class BlockComponent : public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	BlockComponent(int row, int column,const glm::vec2& blockPos, int blockSize, bool QBertWalkable = true, bool enemyWalkable = true);
	virtual ~BlockComponent();

	//------COPY CONSTRUCTORS------
	BlockComponent(const BlockComponent&) = delete;
	BlockComponent(BlockComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	BlockComponent operator=(const BlockComponent&) = delete;
	BlockComponent& operator=(BlockComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void BlockTouched(EntityInfo info) = 0;
	bool IsOccupied(EntityInfo info);
	bool IsWalkable(EntityInfo info);
	virtual bool IsCompleted() { return true; };
	virtual void Update() override {};
	virtual void Render() override {};
	virtual void Reset() {};
	glm::vec2 GetStandPosition(BlockSide side = BlockSide::Top);

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	glm::vec2 m_BlockPosition;
	int m_Row;
	int m_Column;
	int m_BlockSize;

	bool m_QBertWalkable;
	bool m_EnemyWalkable;
};

