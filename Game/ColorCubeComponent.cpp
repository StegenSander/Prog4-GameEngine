#include "MiniginPCH.h"
#include "ColorCubeComponent.h"
#include "LevelComponent.h"
#include "TextureComponent.h"
#include "EntityComponent.h"
#include "Scene.h"
#include "ScoreComponent.h"


ColorCubeComponent::ColorCubeComponent(int row, int column, const glm::vec2& blockPos, int blockSize
	, LevelComponent* pLevel, const std::weak_ptr<TextureComponent>& pTexture
	, int maxColorLevel, bool revertible)
	: BlockComponent(row,column, blockPos,blockSize,pLevel,true,true)
	, m_pTexture{pTexture}
	, m_MaxColorLevel{maxColorLevel}
	, m_IsRevertable{revertible}
{
}

ColorCubeComponent::~ColorCubeComponent()
{
}

void ColorCubeComponent::BlockTouched(const EntityInfo& info)
{
	switch (info.Type)
	{
	case EntityType::QBert:
		ColorCube();
		break;
	case EntityType::UggAndWrongway:
		break;
	case EntityType::SlickAndSam:
		UnColorCube();
		break;
	}
}

bool ColorCubeComponent::IsCompleted()
{
	return m_MaxColorLevel == m_ColorLevel;
}

void ColorCubeComponent::Update()
{
}

void ColorCubeComponent::FullReset()
{
	m_ColorLevel = 0;
	UpdateTexture();
}

void ColorCubeComponent::ColorCube()
{
	if (m_ColorLevel < m_MaxColorLevel)
	{
		m_ColorLevel++;
		auto score = m_pGameObject->GetScene()->FindObjectOfType<ScoreComponent>();
		if (!score.expired() && score.lock().get() != nullptr)
		{
			score.lock()->AddScore(25);
		}
		UpdateTexture();
	}
	else if (m_IsRevertable)
	{
		UnColorCube();
	}
}

void ColorCubeComponent::UnColorCube()
{
	if (m_ColorLevel > 0)
	{
		m_ColorLevel--;
		UpdateTexture();
	}
}

void ColorCubeComponent::UpdateTexture()
{
	if (m_pTexture.expired()) return;

	m_pTexture.lock()->SetTexture("LevelBlock/LevelBlock0_" + std::to_string(m_ColorLevel) + ".png");
}
