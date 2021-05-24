#include "MiniginPCH.h"
#include "BlockComponent.h"

BlockComponent::BlockComponent(int row, int column, bool QBertWalkable, bool enemyWalkable)
	: m_Row {row}
	, m_Column {column}
	, m_QBertWalkable {QBertWalkable}
	, m_EnemyWalkable {enemyWalkable}
{
}

BlockComponent::~BlockComponent()
{
}
