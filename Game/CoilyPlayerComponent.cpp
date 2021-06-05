#include "MiniginPCH.h"
#include "CoilyPlayerComponent.h"
#include "Scene.h"
#include "InputManager.h"
#include "GameTime.h"
#include "LevelNavigatorComponent.h"
#include "TextureComponent.h"

CoilyPlayerComponent::CoilyPlayerComponent(
	const std::weak_ptr<LevelNavigatorComponent>& pNavigator
	, const std::weak_ptr<GameControllerComponent>& pGameController
	, const std::weak_ptr<TextureComponent>& pTexture
	, int spawnIndex, DWORD gamePadIndex, float timeBetweenMoves)
	: EntityComponent(pGameController,EntityType::Coily)
	, m_pNavigator{pNavigator}
	, m_pTexture{pTexture}
	, m_SpawnIndex{spawnIndex}
	, m_TimeBetweenMoves{timeBetweenMoves}
	, m_HasTransformed{false}
	, m_GamepadIndex{gamePadIndex}
{
	m_TimeUntilNextMove = m_TimeBetweenMoves;
}

CoilyPlayerComponent::~CoilyPlayerComponent()
{
	if (m_pGameObject->GetScene())
	{
		m_pGameObject->GetScene()->GetSceneData()->pInputManager->MarkForDeleteByIdentifier(m_pGameObject);
	}
}

void CoilyPlayerComponent::Update()
{

	m_TimeUntilNextMove -= GameTime::GetInstance().GetDeltaTime();
	
	if (!m_HasTransformed && m_TimeUntilNextMove < 0) //Egg Movement
	{
		EggMove();
	}
	else //Free player movement
	{
		PlayerMove();
	}
	
}

MoveResult CoilyPlayerComponent::FullReset()
{
	Transform(true);
	return m_pNavigator.lock()->MoveToSquare(m_SpawnIndex, this);
}

void CoilyPlayerComponent::Despawn()
{
	m_pGameObject->MarkForDelete();
}

void CoilyPlayerComponent::Notify(EventType type, EventData*)
{
	switch (type)
	{
	case EventType::PlayerDamageTaken:
	case EventType::PlayerKilled:
	case EventType::PlayerFallen:
		Despawn();
		break;
	}
}

void CoilyPlayerComponent::Move(Direction direction)
{
	if (m_TimeUntilNextMove < 0)
	{
		m_pNavigator.lock()->Move(direction, this);
		m_TimeUntilNextMove = m_TimeBetweenMoves;
	}
}

void CoilyPlayerComponent::Transform(bool isEgg)
{
	m_HasTransformed = !isEgg;
	if (!m_pTexture.expired())
	{
		if (isEgg)
		{
			m_pTexture.lock()->SetTexture("Enemies/coily1.png");
		}
		else
		{
			m_pTexture.lock()->SetTexture("Enemies/coily2.png");
		}
	}
}

void CoilyPlayerComponent::EggMove()
{
	bool moveLeft = bool(rand() % 2); //is 0 or 1

	MoveResult moveResult;
	if (moveLeft) moveResult = m_pNavigator.lock()->Move(Direction::SouthWest, this);
	else moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);

	if (moveResult.BlockOccupied)
	{
		moveLeft = !moveLeft;
		if (moveLeft) moveResult = m_pNavigator.lock()->Move(Direction::SouthWest, this);
		else moveResult = m_pNavigator.lock()->Move(Direction::SouthEast, this);
	}

	if (!moveResult.ValidMove) Transform(false);

	m_TimeUntilNextMove = m_TimeBetweenMoves;
}

void CoilyPlayerComponent::PlayerMove()
{
	auto sceneData = m_pGameObject->GetScene()->GetSceneData();
	JoystickValue value = sceneData->pInputManager->GetJoystickValue(m_GamepadIndex, true);

	const float threshhold = 0.3f;
	if (value.x > threshhold && value.y > threshhold)
	{
		Move(Direction::NorthEast);
	}

	else if (value.x < -threshhold && value.y >threshhold)
	{
		Move(Direction::NorthWest);
	}

	else if (value.x < -threshhold && value.y < -threshhold)
	{
		Move(Direction::SouthWest);
	}

	else if (value.x > threshhold && value.y < -threshhold)
	{
		Move(Direction::SouthEast);
	}
}
