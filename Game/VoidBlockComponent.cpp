#include "MiniginPCH.h"
#include "VoidBlockComponent.h"
#include "LevelComponent.h"
#include "EntityComponent.h"

VoidBlockComponent::VoidBlockComponent(int row, int column, const glm::vec2& blockPos, int blockSize, LevelComponent* pLevel)
	: BlockComponent(row,column, blockPos,blockSize,pLevel,true,false)
{
}

VoidBlockComponent::~VoidBlockComponent()
{
}

void VoidBlockComponent::BlockTouched(const EntityInfo& info)
{
	if (info.Type == EntityType::QBert)
	{
		m_pLevel->PlayerDamaged();
	}
}
