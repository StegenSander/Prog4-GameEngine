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
#include "VoidBlockComponent.h"
#include "HealthComponent.h"
#include "GameControllerComponent.h"

LevelComponent::LevelComponent(int rows, int blockSize, const std::weak_ptr<GameControllerComponent>& pGameController)
	: m_Rows{rows +2}
	, m_BlockSize{blockSize}
	, m_pGameController(pGameController)
	, Listener(pGameController)
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
		if (rowColumn.second == 1 || rowColumn.second == rowColumn.first || rowColumn.first == m_Rows)
		{
			CreateVoidBLock(rowColumn, pos);
		}
		else CreateColorCube(rowColumn,pos);
	}
}


void LevelComponent::CreateColorCube(const std::pair<int, int>& rowColumn,const glm::vec3& pos)
{
	using namespace dae;
	std::shared_ptr<GameObject> block{ new GameObject() };
	std::shared_ptr<TextureComponent> textureComponent(new TextureComponent{ "LevelBlock/LevelBlock0_0.png",{0,0},{m_BlockSize,m_BlockSize} });
	block->AddComponent(textureComponent);
	m_pGameObject->GetScene()->AddObject(block);

	glm::vec3 blockPos{ pos.x + (rowColumn.second * m_BlockSize) - (rowColumn.first * m_BlockSize) / 2
		, pos.y + rowColumn.first * (m_BlockSize / 4 * 3)
		, pos.z };
	block->GetTransform().SetPosition(blockPos);


	std::shared_ptr<BlockComponent> blockComponent(new ColorCubeComponent{ rowColumn.first,rowColumn.second,{blockPos.x + m_BlockSize / 4,blockPos.y - m_BlockSize / 4},this,textureComponent });
	block->AddComponent(blockComponent);
	m_Level.push_back(blockComponent);
}

void LevelComponent::CreateVoidBLock(const std::pair<int, int>& rowColumn, const glm::vec3& pos)
{
	using namespace dae;
	std::shared_ptr<GameObject> block{ new GameObject() };
	m_pGameObject->GetScene()->AddObject(block);

	glm::vec3 blockPos{ pos.x + (rowColumn.second * m_BlockSize) - (rowColumn.first * m_BlockSize) / 2
		, pos.y + rowColumn.first * (m_BlockSize / 4 * 3)
		, pos.z };
	block->GetTransform().SetPosition(blockPos);


	std::shared_ptr<BlockComponent> blockComponent(new VoidBlockComponent{ rowColumn.first,rowColumn.second,{blockPos.x + m_BlockSize / 4,blockPos.y - m_BlockSize / 4},this });
	block->AddComponent(blockComponent);
	m_Level.push_back(blockComponent);
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

		for (auto& block : m_Level)
		{
			block->Reset();
		}
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
	for (const auto& block : m_Level)
	{
		if (!block->IsCompleted()) return false;
	}
	return true;
}

void LevelComponent::PlayerDamaged()
{
	std::cout << "player hit\n";
	m_pGameController.lock()->PlayerDamaged();
}
void LevelComponent::Notify(EventType type, EventData* )
{
	switch (type)
	{
	case EventType::PlayerDamageTaken:
		break;
	case EventType::PlayerKilled:
		for (auto& block : m_Level)
		{
			block->Reset();
		}
		break;
	}
}
LevelComponent::~LevelComponent()
{
}

void LevelComponent::Update()
{
}
