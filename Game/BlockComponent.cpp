#include "MiniginPCH.h"
#include "BlockComponent.h"

BlockComponent::BlockComponent(int row, int column, const glm::vec2& standPos, bool QBertWalkable, bool enemyWalkable)
	: m_Row {row}
	, m_Column {column}
	, m_QBertWalkable {QBertWalkable}
	, m_EnemyWalkable {enemyWalkable}
	, m_StandPosition{standPos}
{
}

BlockComponent::~BlockComponent()
{
}
