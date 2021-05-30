#include "MiniginPCH.h"
#include "BlockComponent.h"
#include "LevelComponent.h"
#include "EntityComponent.h"

BlockComponent::BlockComponent(int row, int column, const glm::vec2& blockPos,int blockSize, LevelComponent* pLevel, bool QBertWalkable, bool enemyWalkable)
	: m_Row {row}
	, m_Column {column}
	, m_QBertWalkable {QBertWalkable}
	, m_EnemyWalkable {enemyWalkable}
	, m_BlockPosition{blockPos}
	, m_BlockSize{blockSize}
	, m_pLevel{pLevel}
{
}

BlockComponent::~BlockComponent()
{
}

void BlockComponent::RegisterEntity(const EntityInfo& info)
{
	if (m_CurrentEntity.Behaviour == nullptr)
	{
		m_CurrentEntity = info;
	}
	else
	{
		//m_CurrentEntity = info;
		//Collision
		std::cout << "Collision Detected\n";
		m_pLevel->HandleCollision(m_CurrentEntity, info);
	}
}

void BlockComponent::UnRegisterEntity()
{
	m_CurrentEntity.Behaviour = nullptr;
}

bool BlockComponent::IsOccupied(const EntityInfo& info)
{
	if (m_CurrentEntity.Behaviour == nullptr) return false;
	if (info.Type == EntityType::QBert)
	{ 
		//The player can move to any square except a square where another QBERT is
		return m_CurrentEntity.Type == EntityType::QBert;
	}
	return (m_CurrentEntity.Type != EntityType::QBert);
	//return false;
}

bool BlockComponent::IsWalkable(const EntityInfo& info)
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
