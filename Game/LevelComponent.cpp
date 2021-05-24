#include "MiniginPCH.h"
#include "LevelComponent.h"
#include "ExtraMath.h"
#include "GameObject.h"
#include "Scene.h"

//Component
#include "TextureComponent.h"
#include "Transform.h"

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
		using namespace dae;
		std::shared_ptr<GameObject> block{ new GameObject() };
		//std::shared_ptr<LevelComponent> levelComponent(new LevelComponent{ 5 });
		std::shared_ptr<TextureComponent> textureComponent(new TextureComponent{ "LevelBlock/LevelBlock0_0_0.png",{0,0},{m_BlockSize,m_BlockSize} });
		block->AddComponent(textureComponent);
		m_pGameObject->GetScene()->AddObject(block);

		auto rowColumn = ExtraMath::PyramidGetCoordFromIndex(i);
		block->GetTransform().SetPosition({pos.x + (rowColumn.second* m_BlockSize) - (rowColumn.first * m_BlockSize)/2
			, pos.y + rowColumn.first * (m_BlockSize/4*3)
			, pos.z });
	}
}

LevelComponent::~LevelComponent()
{
}

void LevelComponent::Update()
{
}
