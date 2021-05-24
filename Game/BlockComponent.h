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
	BlockComponent(int row, int column,const glm::vec2& standPos, bool QBertWalkable = true, bool enemyWalkable = true);
	virtual ~BlockComponent();

	//------COPY CONSTRUCTORS------
	BlockComponent(const BlockComponent&) = delete;
	BlockComponent(BlockComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	BlockComponent operator=(const BlockComponent&) = delete;
	BlockComponent& operator=(BlockComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	virtual void BlockTouched(EntityType ) {};
	virtual bool IsCompleted() { return true; };
	virtual void Update() override {};
	virtual void Render() override {};
	glm::vec2 GetStandPosition() { return m_StandPosition; }

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	glm::vec2 m_StandPosition;
	int m_Row;
	int m_Column;

	bool m_QBertWalkable;
	bool m_EnemyWalkable;
};

