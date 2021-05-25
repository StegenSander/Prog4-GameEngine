#include "MiniginPCH.h"
#include "LevelComponent.h"
#include "ExtraMath.h"
#include "GameObject.h"
#include "Scene.h"

//Component
#include "TextureComponent.h"
#include "Transform.h"
#include "BlockComponent.h"
#include "LevelNavigatorComponent.h"
#include "ColorCubeComponent.h"

LevelComponent::LevelComponent(int rows, int blockSize)
	: m_Rows{rows}
	,m_BlockSize{blockSize}
{
}

void LevelComponent::CreateLevel()
{
	int totalBlocks = ExtraMath::PyramidAmountOfBlockUntilRow(m_Rows);
	std::cout << "Rows: " << m_Rows << " Totalblocks: " << totalBlocks << std::endl;

	auto& pos =m_pGameObject->GetTransform().GetPosition();
	for (int i = 0; i < totalBlocks; i++)
	{
		auto rowColumn = ExtraMath::PyramidGetCoordFromIndex(i);
		using namespace dae;
		std::shared_ptr<GameObject> block{ new GameObject() };
		std::shared_ptr<TextureComponent> textureComponent(new TextureComponent{ "LevelBlock/LevelBlock0_0.png",{0,0},{m_BlockSize,m_BlockSize} });
		block->AddComponent(textureComponent);
		m_pGameObject->GetScene()->AddObject(block);

		glm::vec3 blockPos{ pos.x + (rowColumn.second * m_BlockSize) - (rowColumn.first * m_BlockSize) / 2
			, pos.y + rowColumn.first * (m_BlockSize / 4 * 3)
			, pos.z };
		block->GetTransform().SetPosition(blockPos);


		std::shared_ptr<BlockComponent> blockComponent(new ColorCubeComponent{ rowColumn.first,rowColumn.second,{blockPos.x + m_BlockSize/4,blockPos.y - m_BlockSize/4},this,textureComponent });
		block->AddComponent(blockComponent);
		m_Level.push_back(blockComponent);
	}
}

std::weak_ptr<BlockComponent> LevelComponent::GetBlockAtIndex(int index)
{
	assert(index < m_Level.size());
	assert(index >= 0);
	return m_Level[index];
}

void LevelComponent::BlockTouched(int row, int column, EntityType type)
{
	BlockTouched(ExtraMath::PyramidAmountOfBlockUntil(row, column), type);

	if (IsLevelFinished())
	{
		std::cout << "Level Finished\n";
	}
}

void LevelComponent::BlockTouched(int index, EntityType type)
{
	assert(index < m_Level.size());
	assert(index >= 0);
	m_Level[index]->BlockTouched(type);
}

bool LevelComponent::IsLevelFinished()
{
	for (auto block : m_Level)
	{
		if (!block->IsCompleted()) return false;
	}
	return true;
}

LevelComponent::~LevelComponent()
{
}

void LevelComponent::Update()
{
}
