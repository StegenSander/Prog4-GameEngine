#include "MiniginPCH.h"
#include "VoidBlockComponent.h"
#include "LevelComponent.h"

VoidBlockComponent::VoidBlockComponent(int row, int column, const glm::vec2& blockPos, int blockSize, LevelComponent* pLevel)
	: BlockComponent(row,column, blockPos,blockSize,true,false)
	, m_pLevel{pLevel}
{
}

VoidBlockComponent::~VoidBlockComponent()
{
}

void VoidBlockComponent::BlockTouched(EntityType type)
{
	if (type == EntityType::QBert)
	{
		m_pLevel->PlayerDamaged();
	}
}
