#include "MiniginPCH.h"
#include "DiscComponent.h"
#include "LevelNavigatorComponent.h"
#include "LevelComponent.h"

DiscComponent::DiscComponent(int row, int column, const glm::vec2& blockPos, int blockSize, LevelComponent* pLevel)
	: BlockComponent(row, column, blockPos, blockSize, pLevel, true, false)
{
}

DiscComponent::~DiscComponent()
{
}

void DiscComponent::BlockTouched(const EntityInfo& info)
{
	if (info.Type == EntityType::QBert)
	{
		info.Behaviour->GetGameObject()->GetComponent<LevelNavigatorComponent>().lock()->MoveToSquare(3, 2, info.Behaviour);
		m_pLevel->SetBlockToVoid(m_Row, m_Column);
	}
}
