#include "MiniginPCH.h"
#include "VoidBlockComponent.h"
#include "LevelComponent.h"

VoidBlockComponent::VoidBlockComponent(int row, int column, const glm::vec2& standPos, LevelComponent* pLevel)
	: BlockComponent(row,column,standPos,true,false)
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
