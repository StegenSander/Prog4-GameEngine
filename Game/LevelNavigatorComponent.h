#pragma once
#include "BaseComponent.h"

enum class Direction
{
	NorthEast,
	SouthEast,
	SouthWest,
	NorthWest,
};
enum class EntityType;
class LevelComponent;
class BlockComponent;
class LevelNavigatorComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	LevelNavigatorComponent(const std::weak_ptr<LevelComponent>& pLevel, EntityType type);
	virtual ~LevelNavigatorComponent();

	//------COPY CONSTRUCTORS------
	LevelNavigatorComponent(const LevelNavigatorComponent&) = delete;
	LevelNavigatorComponent(LevelNavigatorComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	LevelNavigatorComponent operator=(const LevelNavigatorComponent&) = delete;
	LevelNavigatorComponent& operator=(LevelNavigatorComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	//Return if move was succesfull or not
	BlockComponent* MoveToSquare(int row, int column);
	//Return if move was succesfull or not
	BlockComponent* MoveToSquare(int index);
	//Return if move was succesfull or not
	BlockComponent* Move(Direction dir);
	void Update() override {};

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	std::weak_ptr<LevelComponent> m_pLevel{};
	int m_CurrentRow{1};
	int m_CurrentColumn{1};
	EntityType m_Type;
};

