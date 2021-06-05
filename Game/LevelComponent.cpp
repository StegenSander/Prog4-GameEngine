#include "MiniginPCH.h"
#include "LevelComponent.h"
#include "ExtraMath.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameScene.h"

//Component
#include "TextureComponent.h"
#include "Transform.h"
#include "BlockComponent.h"
#include "LevelNavigatorComponent.h"
#include "ColorCubeComponent.h"
#include "VoidBlockComponent.h"
#include "HealthComponent.h"
#include "GameControllerComponent.h"
#include "EntityComponent.h"
#include "DiscComponent.h"
#include "ScoreComponent.h"


LevelComponent::LevelComponent(int rows, int blockSize, int discRow
	, const std::weak_ptr<GameControllerComponent>& pGameController
	, int maxColorLevel, bool revertible)
	: m_Rows{rows +2}
	, m_BlockSize{blockSize}
	, m_pGameController(pGameController)
	, Listener(pGameController)
	, m_DiscRow{discRow}
	, m_MaxColorLevel{maxColorLevel}
	, m_Revertible{revertible}
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
			CreateVoidBlock(rowColumn, pos);
		}
		else CreateColorCube(rowColumn,pos);
	}

	InitiliazeDiscs(m_DiscRow);
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


	std::shared_ptr<BlockComponent> blockComponent(
		new ColorCubeComponent{ rowColumn.first,rowColumn.second,{blockPos.x + m_BlockSize / 4,blockPos.y - m_BlockSize / 4}
		,m_BlockSize,this,textureComponent, m_MaxColorLevel,m_Revertible });
	block->AddComponent(blockComponent);
	m_Level.push_back(blockComponent);
}

void LevelComponent::CreateVoidBlock(const std::pair<int, int>& rowColumn, const glm::vec3& pos)
{
	using namespace dae;
	std::shared_ptr<GameObject> block{ new GameObject() };
	m_pGameObject->GetScene()->AddObject(block);

	glm::vec3 blockPos{ pos.x + (rowColumn.second * m_BlockSize) - (rowColumn.first * m_BlockSize) / 2
		, pos.y + rowColumn.first * (m_BlockSize / 4 * 3)
		, pos.z };
	block->GetTransform().SetPosition(blockPos);


	std::shared_ptr<BlockComponent> blockComponent(new VoidBlockComponent{ rowColumn.first,rowColumn.second,{blockPos.x + m_BlockSize / 4,blockPos.y - m_BlockSize / 4},m_BlockSize,this });
	block->AddComponent(blockComponent);
	m_Level.push_back(blockComponent);
}

void LevelComponent::CreateDisc(const std::pair<int, int>& rowColumn, const glm::vec3& pos)
{
	using namespace dae;
	std::shared_ptr<GameObject> block{ new GameObject() };
	m_pGameObject->GetScene()->AddObject(block);

	std::shared_ptr<TextureComponent> textureComponent(new TextureComponent{ "LevelBlock/Disc.png",{0,0},{m_BlockSize,m_BlockSize} });
	block->AddComponent(textureComponent);
	textureComponent->SetSize({32,32});
	textureComponent->SetPositionOffset({16, 16 });

	glm::vec3 blockPos{ pos.x + (rowColumn.second * m_BlockSize) - (rowColumn.first * m_BlockSize) / 2
		, pos.y + rowColumn.first * (m_BlockSize / 4 * 3)
		, pos.z };
	block->GetTransform().SetPosition(blockPos);


	std::shared_ptr<BlockComponent> blockComponent(new DiscComponent{ rowColumn.first,rowColumn.second,{blockPos.x + m_BlockSize / 4,blockPos.y - m_BlockSize / 4},m_BlockSize,this });
	block->AddComponent(blockComponent);
	m_Level.push_back(blockComponent);
}


std::weak_ptr<BlockComponent> LevelComponent::GetBlockAtIndex(int index)
{
	assert(size_t(index) < m_Level.size());
	assert(index >= 0);
	return m_Level[index];
}

void LevelComponent::SetBlockToVoid(int row, int column)
{
	auto& pos = m_pGameObject->GetTransform().GetPosition();

	using namespace dae;
	std::shared_ptr<GameObject> block{ new GameObject() };
	m_pGameObject->GetScene()->AddObject(block);

	glm::vec3 blockPos{ pos.x + (column * m_BlockSize) - (row * m_BlockSize) / 2
		, pos.y + row * (m_BlockSize / 4 * 3)
		, pos.z };
	block->GetTransform().SetPosition(blockPos);
	std::shared_ptr<BlockComponent> blockComponent(new VoidBlockComponent{ row,column,{blockPos.x + m_BlockSize / 4,blockPos.y - m_BlockSize / 4},m_BlockSize,this });
	block->AddComponent(blockComponent);

	int index = ExtraMath::PyramidAmountOfBlockUntil(row, column);
	m_Level[index]->GetGameObject()->MarkForDelete();
	m_Level[index] = blockComponent;
}

void LevelComponent::SetBlockToDisc(int row, int column)
{
	auto& pos = m_pGameObject->GetTransform().GetPosition();

	using namespace dae;
	std::shared_ptr<GameObject> block{ new GameObject() };
	m_pGameObject->GetScene()->AddObject(block);

	std::shared_ptr<TextureComponent> textureComponent(new TextureComponent{ "LevelBlock/Disc.png",{0,0},{m_BlockSize,m_BlockSize} });
	block->AddComponent(textureComponent);
	textureComponent->SetSize({ 32,32 });
	textureComponent->SetPositionOffset({ 16, 16 });

	glm::vec3 blockPos{ pos.x + (column * m_BlockSize) - (row * m_BlockSize) / 2
		, pos.y + row * (m_BlockSize / 4 * 3)
		, pos.z };
	block->GetTransform().SetPosition(blockPos);


	std::shared_ptr<BlockComponent> blockComponent(new DiscComponent{ row,column,{blockPos.x + m_BlockSize / 4,blockPos.y - m_BlockSize / 4},m_BlockSize,this });
	block->AddComponent(blockComponent);

	int index = ExtraMath::PyramidAmountOfBlockUntil(row, column);
	m_Level[index]->GetGameObject()->MarkForDelete();
	m_Level[index] = blockComponent;
}

void LevelComponent::InitiliazeDiscs(int row)
{
	SetBlockToDisc(row, 1);
	SetBlockToDisc(row, row);
}

void LevelComponent::BlockTouched(int row, int column, const EntityInfo& info)
{
	BlockTouched(ExtraMath::PyramidAmountOfBlockUntil(row, column),info);

	if (IsLevelFinished())
	{
		LevelFinished();
		
	}
}

void LevelComponent::BlockTouched(int index, const EntityInfo& info)
{
	assert(size_t(index) < m_Level.size());
	assert(index >= 0);
	m_Level[index]->BlockTouched(info);
}

bool LevelComponent::IsLevelFinished()
{
	for (const auto& block : m_Level)
	{
		if (!block->IsCompleted()) return false;
	}
	return true;
}

void LevelComponent::LevelFinished()
{
	std::cout << "Level Finished\n";

	//Score
	{
		int discsRemaining = 0;

		//Check left Disc
		auto block = GetBlockAtIndex(ExtraMath::PyramidAmountOfBlockUntil(m_DiscRow, 1));
		auto discComp = block.lock()->GetGameObject()->GetComponent<DiscComponent>();
		if (!discComp.expired() && discComp.lock().get() != nullptr)
		{
			discsRemaining++;
		}

		//Check rightDisc
		block = GetBlockAtIndex(ExtraMath::PyramidAmountOfBlockUntil(m_DiscRow, m_DiscRow));
		discComp = block.lock()->GetGameObject()->GetComponent<DiscComponent>();
		if (!discComp.expired() && discComp.lock().get() != nullptr)
		{
			discsRemaining++;
		}

		//Add Score for remainingDiscs
		auto score = m_pGameObject->GetScene()->FindObjectOfType<ScoreComponent>();
		if (!score.expired() && score.lock().get() != nullptr)
		{
			score.lock()->AddScore(50 * discsRemaining);
		}
	}

	FullReset();

	GameScene* gameScene = dynamic_cast<GameScene*>( m_pGameObject->GetScene());
	if (gameScene)
	{
		gameScene->LoadNextLevel();
	}
}

void LevelComponent::FullReset()
{
	//Reset Blocks
	for (auto& block : m_Level)
	{
		block->FullReset();
	}

	//Reset Discs
	InitiliazeDiscs(m_DiscRow);
}


void LevelComponent::PlayerDamaged()
{
	if (!m_pGameController.expired()) m_pGameController.lock()->PlayerDamaged();
}
void LevelComponent::PlayerFallen()
{
	if(!m_pGameController.expired()) m_pGameController.lock()->PlayerOffMap();
}
void LevelComponent::Notify(EventType type, EventData* )
{
	switch (type)
	{
	case EventType::PlayerKilled:
		FullReset();

		GameScene* gameScene = dynamic_cast<GameScene*>(m_pGameObject->GetScene());
		if (gameScene)
		{
			gameScene->LoadMainMenu();
		}
		break;
	}
}
void LevelComponent::HandleCollision(const EntityInfo& firstObject, const EntityInfo& secondObject)
{
	//Find Which object is qbert and which the other one
	EntityInfo QBertInfo;
	EntityInfo otherInfo;
	if (firstObject.Type == EntityType::QBert)
	{
		QBertInfo = firstObject;
		otherInfo = secondObject;
	}
	else if (secondObject.Type == EntityType::QBert)
	{
		QBertInfo = secondObject;
		otherInfo = firstObject;
	}
	else //No Qbert part of the collision
	{
		std::cout << "No collision with QBert happened\n";
		return;
	}

	//Check Collision
	switch (otherInfo.Type)
	{
	case EntityType::Coily:
	case EntityType::UggAndWrongway:
		PlayerDamaged();
		break;
	case EntityType::SlickAndSam:
		otherInfo.Behaviour->Despawn();
		auto score = m_pGameObject->GetScene()->FindObjectOfType<ScoreComponent>();
		if (!score.expired() && score.lock().get() != nullptr)
		{
			score.lock()->AddScore(300);
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
