#include "MiniginPCH.h"
#include "ColorCubeComponent.h"
#include "LevelComponent.h"
#include "TextureComponent.h"


ColorCubeComponent::ColorCubeComponent(int row, int column, const glm::vec2& standPos, LevelComponent* pLevel, const std::weak_ptr<TextureComponent>& pTexture)
	: BlockComponent(row,column,standPos,true,true)
	, m_pLevel{ pLevel }
	, m_pTexture{pTexture}
{
}

ColorCubeComponent::~ColorCubeComponent()
{
}

void ColorCubeComponent::BlockTouched(EntityType type)
{
	switch (type)
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

void ColorCubeComponent::ColorCube()
{
	if (m_ColorLevel < m_MaxColorLevel)
	{
		m_ColorLevel++;
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
