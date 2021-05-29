#include "MiniginPCH.h"
#include "LevelNavigatorComponent.h"
#include "LevelComponent.h"
#include "ExtraMath.h"
#include "Transform.h"
#include "BlockComponent.h"
#include "VoidBlockComponent.h"
#include "EntityComponent.h"

LevelNavigatorComponent::LevelNavigatorComponent(const std::weak_ptr<LevelComponent>& pLevel)
	: m_pLevel{pLevel}
{
}

LevelNavigatorComponent::~LevelNavigatorComponent()
{
}

MoveResult LevelNavigatorComponent::MoveToSquare(int row, int column, EntityComponent* entityComp)
{
	MoveResult result{};
	if (!IsValidPyramidCoord(row,column)) return result; //Will return an invalid pointer/nullptr

	int index = ExtraMath::PyramidAmountOfBlockUntil(row, column);
	auto block = m_pLevel.lock().get()->GetBlockAtIndex(index);
	if (!block.lock()->IsWalkable(entityComp->GetInfo())) return result;
	result.validMove = true;

	if (block.lock()->IsOccupied(entityComp->GetInfo()))
	{
		result.blockOccupied = true;
		return result;
	}
	auto standPos = block.lock().get()->GetStandPosition(BlockSide::Top); 
	m_pGameObject->GetTransform().SetPosition({ standPos.x,standPos.y,0 });

	m_CurrentRow = row;
	m_CurrentColumn = column;
	m_pLevel.lock()->BlockTouched(m_CurrentRow,m_CurrentColumn, entityComp->GetInfo());
	result.blockTouched = block.lock().get();
	result.didMove = true;
	//Pointer is not dangling, Copy of the weak/shared pointer does get destroyed
	//but the raw pointer which gets returned is still a valid pointer
	return result;
}

MoveResult LevelNavigatorComponent::MoveToSquare(int index, EntityComponent* entityComp)
{
	auto rowColumn = ExtraMath::PyramidGetCoordFromIndex(index);
	return MoveToSquare(rowColumn.first, rowColumn.second, entityComp);
}

MoveResult LevelNavigatorComponent::Move(Direction dir, EntityComponent* entityComp)
{
	switch (dir)
	{
	case Direction::NorthEast:
		return MoveToSquare(m_CurrentRow - 1, m_CurrentColumn, entityComp);
		break;
	case Direction::SouthEast:
		return MoveToSquare(m_CurrentRow + 1, m_CurrentColumn+1, entityComp);
		break;
	case Direction::SouthWest:
		return MoveToSquare(m_CurrentRow + 1, m_CurrentColumn, entityComp);
		break;
	case Direction::NorthWest:
		return MoveToSquare(m_CurrentRow - 1, m_CurrentColumn - 1, entityComp);
		break;
	}
	return MoveResult(); //Will return an invalid pointer/nullptr
}

bool LevelNavigatorComponent::IsValidPyramidCoord(int row, int column) noexcept
{
	return !(row < 1
		|| column < 1
		|| row > m_pLevel.lock().get()->AmountOfRows()
		|| column > row);
}
