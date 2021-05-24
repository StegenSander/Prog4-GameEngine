#pragma once
#include "BaseComponent.h"

enum class EntityType
{
	QBert,
	Purple,
	Green,
};
class BlockComponent : public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	BlockComponent(int row, int column, bool QBertWalkable = true, bool enemyWalkable = true);
	virtual ~BlockComponent();

	//------COPY CONSTRUCTORS------
	BlockComponent(const BlockComponent&) = delete;
	BlockComponent(BlockComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	BlockComponent operator=(const BlockComponent&) = delete;
	BlockComponent& operator=(BlockComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void BlockTouched(EntityType type) = 0;
	virtual bool IsCompleted() { return true; };
	virtual void Update() override = 0;
	virtual void Render() override {};

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	int m_Row;
	int m_Column;

	bool m_QBertWalkable;
	bool m_EnemyWalkable;
};

