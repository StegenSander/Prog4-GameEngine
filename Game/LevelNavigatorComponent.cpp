#include "MiniginPCH.h"
#include "LevelNavigatorComponent.h"
#include "LevelComponent.h"
#include "ExtraMath.h"
#include "Transform.h"
#include "BlockComponent.h"

LevelNavigatorComponent::LevelNavigatorComponent(const std::weak_ptr<LevelComponent>& pLevel)
	: m_pLevel{pLevel}
{
}

LevelNavigatorComponent::~LevelNavigatorComponent()
{
}

void LevelNavigatorComponent::MoveToSquare(int row, int column)
{
	int index = ExtraMath::PyramidAmountOfBlockUntil(row, column);
	if (row < 1 || column < 1 || row > m_pLevel.lock().get()->AmountOfRows() ||column > m_pLevel.lock().get()->AmountOfRows()) return;
	auto block = m_pLevel.lock().get()->GetBlockAtIndex(index);
	auto standPos = block.lock().get()->GetStandPosition(); 
	m_pGameObject->GetTransform().SetPosition({ standPos.x,standPos.y,0 });

	m_CurrentRow = row;
	m_CurrentColumn = column;
}

void LevelNavigatorComponent::Move(Direction dir)
{
	switch (dir)
	{
	case Direction::NorthEast:
		MoveToSquare(m_CurrentRow - 1, m_CurrentColumn);
		break;
	case Direction::SouthEast:
		MoveToSquare(m_CurrentRow + 1, m_CurrentColumn+1);
		break;
	case Direction::SouthWest:
		MoveToSquare(m_CurrentRow + 1, m_CurrentColumn);
		break;
	case Direction::NorthWest:
		MoveToSquare(m_CurrentRow - 1, m_CurrentColumn - 1);
		break;
	}
}
