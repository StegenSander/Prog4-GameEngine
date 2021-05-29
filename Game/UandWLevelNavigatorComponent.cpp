#include "MiniginPCH.h"
#include "UandWLevelNavigatorComponent.h"
#include "LevelComponent.h"
#include "ExtraMath.h"
#include "Transform.h"
#include "BlockComponent.h"
#include "VoidBlockComponent.h"
#include "EntityComponent.h"

UandWLevelNavigatorComponent::UandWLevelNavigatorComponent(const std::weak_ptr<LevelComponent>& pLevel, BlockSide blockside)
	:LevelNavigatorComponent(pLevel)
	, m_BlockSide(blockside)
{
}

UandWLevelNavigatorComponent::~UandWLevelNavigatorComponent()
{
}

MoveResult UandWLevelNavigatorComponent::MoveToSquare(int row, int column, EntityComponent* entityComp)
{
	//Prepare result
	MoveResult result;
	result.blockTouched = nullptr;
	result.didMove = false;
	result.blockOccupied = false;
	result.validMove = false;

	//Check for a valid coordinate
	if (!IsValidPyramidCoord(row, column)) return result;

	//Get the block
	int index = ExtraMath::PyramidAmountOfBlockUntil(row, column);
	auto block = m_pLevel.lock().get()->GetBlockAtIndex(index);
	
	//Check if the block is walkable for the current Entity
	if (!block.lock()->IsWalkable(entityComp->GetInfo())) return result;
	result.validMove = true;

	//Check if the block is occupied for the current Entity
	if (block.lock()->IsOccupied(entityComp->GetInfo()))
	{
		result.blockOccupied = true;
		return result;
	}

	//Move the entity
	auto standPos = block.lock().get()->GetStandPosition(m_BlockSide);
	m_pGameObject->GetTransform().SetPosition({ standPos.x,standPos.y,0 });

	//Update Variables
	m_CurrentRow = row;
	m_CurrentColumn = column;
	m_pLevel.lock()->BlockTouched(m_CurrentRow, m_CurrentColumn, entityComp->GetInfo());

	//fill in results
	//Pointer is not dangling, Copy of the weak/shared pointer does get destroyed
	//but the raw pointer which gets returned is still a valid pointer
	result.blockTouched = block.lock().get();
	result.didMove = true;

	return result;
}
