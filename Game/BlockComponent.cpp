#include "MiniginPCH.h"
#include "BlockComponent.h"
#include "LevelComponent.h"

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

bool BlockComponent::IsWalkable(EntityType type)
{
	switch (type)
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
