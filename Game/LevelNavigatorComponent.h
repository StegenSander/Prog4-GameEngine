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
enum class BlockSide;
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
	virtual BlockComponent* MoveToSquare(int row, int column);
	//Return if move was succesfull or not
	BlockComponent* MoveToSquare(int index);
	//Return if move was succesfull or not
	BlockComponent* Move(Direction dir);
	void Update() override {};
	bool IsValidPyramidCoord(int row, int column) noexcept;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
	std::weak_ptr<LevelComponent> m_pLevel{};
	int m_CurrentRow{ 1 };
	int m_CurrentColumn{ 1 };
	EntityType m_Type;
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};

