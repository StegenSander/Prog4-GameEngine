#include "MiniginPCH.h"
#include "BlockComponent.h"
#include "LevelComponent.h"
#include "EntityComponent.h"

BlockComponent::BlockComponent(int row, int column, const glm::vec2& blockPos,int blockSize, bool QBertWalkable, bool enemyWalkable)
	: m_Row {row}
	, m_Column {column}
	, m_QBertWalkable {QBertWalkable}
	, m_EnemyWalkable {enemyWalkable}
	, m_BlockPosition{blockPos}
	, m_BlockSize{blockSize}
{
}

BlockComponent::~BlockComponent()
{
}

bool BlockComponent::IsOccupied(EntityInfo info)
{
	if (info.Type == EntityType::QBert) return false;
	return false;
}

bool BlockComponent::IsWalkable(EntityInfo info)
{
	switch (info.Type)
	{
	case EntityType::QBert:
		return m_QBertWalkable;
		break;
	case EntityType::Coily:
	case EntityType::UggAndWrongway:
	case EntityType::SlickAndSam:
		return m_EnemyWalkable;
	default:
		break;
	}

	return false;
}

glm::vec2 BlockComponent::GetStandPosition(BlockSide side)
{
	switch (side)
	{
	case BlockSide::Top:
		return {m_BlockPosition.x, m_BlockPosition.y };
		break;
	case BlockSide::Left:
		return { m_BlockPosition.x - m_BlockSize/4, m_BlockPosition.y + m_BlockSize / 4 *3 };
		break;
	case BlockSide::Right:
		return {m_BlockPosition.x + m_BlockSize / 2, m_BlockPosition.y + m_BlockSize / 4*3 };
		break;
	default:
		return m_BlockPosition;
		break;
	}
}
