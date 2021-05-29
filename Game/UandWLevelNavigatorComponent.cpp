#include "MiniginPCH.h"
#include "UandWLevelNavigatorComponent.h"
#include "LevelComponent.h"
#include "ExtraMath.h"
#include "Transform.h"
#include "BlockComponent.h"
#include "VoidBlockComponent.h"

UandWLevelNavigatorComponent::UandWLevelNavigatorComponent(const std::weak_ptr<LevelComponent>& pLevel, EntityType type, BlockSide blockside)
	:LevelNavigatorComponent(pLevel,type)
	, m_BlockSide(blockside)
{
}

UandWLevelNavigatorComponent::~UandWLevelNavigatorComponent()
{
}

BlockComponent* UandWLevelNavigatorComponent::MoveToSquare(int row, int column)
{
	if (!IsValidPyramidCoord(row, column)) return nullptr; //Will return an invalid pointer/nullptr

	int index = ExtraMath::PyramidAmountOfBlockUntil(row, column);
	auto block = m_pLevel.lock().get()->GetBlockAtIndex(index);
	if (!block.lock()->IsWalkable(m_Type)) return nullptr;

	auto standPos = block.lock().get()->GetStandPosition(m_BlockSide);
	m_pGameObject->GetTransform().SetPosition({ standPos.x,standPos.y,0 });

	m_CurrentRow = row;
	m_CurrentColumn = column;
	m_pLevel.lock()->BlockTouched(m_CurrentRow, m_CurrentColumn, m_Type);

	//Pointer is not dangling, Copy of the weak/shared pointer does get destroyed
	//but the raw pointer which gets returned is still a valid pointer
	return block.lock().get();
}
