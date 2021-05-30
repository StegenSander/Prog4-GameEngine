#include "MiniginPCH.h"
#include "LevelNavigatorComponent.h"
#include "LevelComponent.h"
#include "ExtraMath.h"
#include "Transform.h"
#include "BlockComponent.h"
#include "VoidBlockComponent.h"
#include "EntityComponent.h"

LevelNavigatorComponent::LevelNavigatorComponent(const std::weak_ptr<LevelComponent>& pLevel, BlockSide blockside)
	: m_pLevel{pLevel}
	, m_BlockSide{blockside}
{
}

LevelNavigatorComponent::~LevelNavigatorComponent()
{
	UnRegisterFromBlock();
}

MoveResult LevelNavigatorComponent::MoveToSquare(int row, int column, EntityComponent* entityComp)
{
	//Prepare result
	MoveResult result{};

	//Check for a valid coordinate
	if (!IsValidPyramidCoord(row, column)) return result;

	//Get the block
	int index = ExtraMath::PyramidAmountOfBlockUntil(row, column);
	auto block = m_pLevel.lock().get()->GetBlockAtIndex(index);

	//Check if the block is walkable for the current Entity
	if (!block.lock()->IsWalkable(entityComp->GetInfo())) return result;
	result.validMove = true;

	//Check if the block is occupied for the current Entity
	if (GetCorrectBlockAt(row,column).lock()->IsOccupied(entityComp->GetInfo()))
	{
		result.blockOccupied = true;
		return result;
	}

	//Move the entity
	auto standPos = block.lock().get()->GetStandPosition(m_BlockSide);
	m_pGameObject->GetTransform().SetPosition({ standPos.x,standPos.y,0 });

	//Update Variables
	UnRegisterFromBlock();
	m_CurrentRow = row;
	m_CurrentColumn = column;
	m_pLevel.lock()->BlockTouched(m_CurrentRow, m_CurrentColumn, entityComp->GetInfo());
	RegisterOnBlock(entityComp);

	//fill in results
	//Pointer is not dangling, Copy of the weak/shared pointer does get destroyed
	//but the raw pointer which gets returned is still a valid pointer
	result.blockTouched = block.lock().get();
	result.didMove = true;

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
std::weak_ptr<BlockComponent> LevelNavigatorComponent::GetCorrectBlockAt(int row, int column)
{
	int index{};
	switch (m_BlockSide)
	{
	case BlockSide::Left:
		index = ExtraMath::PyramidAmountOfBlockUntil(row + 1, column);
		break;
	case BlockSide::Right:
		index = ExtraMath::PyramidAmountOfBlockUntil(row + 1, column + 1);
		break;
	default:
		index = ExtraMath::PyramidAmountOfBlockUntil(row, column);
		break;
	}
	return m_pLevel.lock()->GetBlockAtIndex(index);
}

void LevelNavigatorComponent::UnRegisterFromBlock()
{
	GetCorrectBlockAt(m_CurrentRow,m_CurrentColumn).lock()->UnRegisterEntity();
}

void LevelNavigatorComponent::RegisterOnBlock(EntityComponent* entityComp)
{
	GetCorrectBlockAt(m_CurrentRow,m_CurrentColumn).lock()->RegisterEntity(entityComp->GetInfo());
}
