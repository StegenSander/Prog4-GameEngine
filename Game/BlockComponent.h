#pragma once
#include "BaseComponent.h"
#include "EntityComponent.h"
#include "DataStructures.h"

class LevelComponent;
class BlockComponent : public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	BlockComponent(int row, int column,const glm::vec2& blockPos, int blockSize, LevelComponent* pLevel, bool QBertWalkable = true, bool enemyWalkable = true);
	virtual ~BlockComponent() = default;

	//------COPY CONSTRUCTORS------
	BlockComponent(const BlockComponent&) = delete;
	BlockComponent(BlockComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	BlockComponent& operator=(const BlockComponent&) = delete;
	BlockComponent& operator=(BlockComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void BlockTouched(const EntityInfo& info) = 0;
	virtual void RegisterEntity(const EntityInfo& info);
	virtual void UnRegisterEntity();
	bool IsOccupied(const EntityInfo& info) const;
	bool IsWalkable(const EntityInfo& info) const;
	virtual bool IsCompleted() const { return true; };
	virtual void Update() override {};
	virtual void Render() override {};
	virtual void FullReset() {};
	glm::vec2 GetStandPosition(BlockSide side = BlockSide::Top) const;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
	LevelComponent* m_pLevel{};
	int m_Row;
	int m_Column;
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	glm::vec2 m_BlockPosition;
	int m_BlockSize;

	bool m_QBertWalkable;
	bool m_EnemyWalkable;

	EntityInfo m_CurrentEntity;
};

