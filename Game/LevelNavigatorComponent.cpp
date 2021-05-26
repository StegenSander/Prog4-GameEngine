#include "MiniginPCH.h"
#include "LevelNavigatorComponent.h"
#include "LevelComponent.h"
#include "ExtraMath.h"
#include "Transform.h"
#include "BlockComponent.h"
#include "VoidBlockComponent.h"

LevelNavigatorComponent::LevelNavigatorComponent(const std::weak_ptr<LevelComponent>& pLevel, EntityType type)
	: m_pLevel{pLevel}
	, m_Type{type}
{
}

LevelNavigatorComponent::~LevelNavigatorComponent()
{
}

BlockComponent* LevelNavigatorComponent::MoveToSquare(int row, int column)
{
	if (row < 1 
		|| column < 1 
		|| row > m_pLevel.lock().get()->AmountOfRows() 
		|| column > row) return nullptr; //Will return an invalid pointer/nullptr

	int index = ExtraMath::PyramidAmountOfBlockUntil(row, column);
	auto block = m_pLevel.lock().get()->GetBlockAtIndex(index);
	if (!block.lock()->IsWalkable(m_Type)) return nullptr;

	auto standPos = block.lock().get()->GetStandPosition(); 
	m_pGameObject->GetTransform().SetPosition({ standPos.x,standPos.y,0 });

	m_CurrentRow = row;
	m_CurrentColumn = column;
	m_pLevel.lock()->BlockTouched(m_CurrentRow,m_CurrentColumn,m_Type);
	
	//Pointer is not dangling, Copy of the weak pointer does get destroyed
	//but the raw pointer which gets returned is still a valid pointer
	return block.lock().get();
}

BlockComponent* LevelNavigatorComponent::MoveToSquare(int index)
{
	auto rowColumn = ExtraMath::PyramidGetCoordFromIndex(index);
	return MoveToSquare(rowColumn.first, rowColumn.second);
}

BlockComponent* LevelNavigatorComponent::Move(Direction dir)
{
	switch (dir)
	{
	case Direction::NorthEast:
		return MoveToSquare(m_CurrentRow - 1, m_CurrentColumn);
		break;
	case Direction::SouthEast:
		return MoveToSquare(m_CurrentRow + 1, m_CurrentColumn+1);
		break;
	case Direction::SouthWest:
		return MoveToSquare(m_CurrentRow + 1, m_CurrentColumn);
		break;
	case Direction::NorthWest:
		return MoveToSquare(m_CurrentRow - 1, m_CurrentColumn - 1);
		break;
	}
	return nullptr; //Will return an invalid pointer/nullptr
}
