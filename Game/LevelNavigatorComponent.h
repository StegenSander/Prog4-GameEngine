#pragma once
#include "BaseComponent.h"

enum class Direction
{
	NorthEast,
	SouthEast,
	SouthWest,
	NorthWest,
};
enum class BlockSide;
class LevelComponent;
class BlockComponent;
class EntityComponent;
struct MoveResult
{
	BlockComponent* blockTouched = nullptr;
	bool blockOccupied = false;
	bool didMove= false;
	bool validMove = false;
};
class LevelNavigatorComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	LevelNavigatorComponent(const std::weak_ptr<LevelComponent>& pLevel);
	virtual ~LevelNavigatorComponent();

	//------COPY CONSTRUCTORS------
	LevelNavigatorComponent(const LevelNavigatorComponent&) = delete;
	LevelNavigatorComponent(LevelNavigatorComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	LevelNavigatorComponent operator=(const LevelNavigatorComponent&) = delete;
	LevelNavigatorComponent& operator=(LevelNavigatorComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	//Return if move was succesfull or not
	virtual MoveResult MoveToSquare(int row, int column, EntityComponent* entityComp);
	//Return if move was succesfull or not
	MoveResult MoveToSquare(int index, EntityComponent* entityComp);
	//Return if move was succesfull or not
	MoveResult Move(Direction dir, EntityComponent* entityComp);

	void Update() override {};
	bool IsValidPyramidCoord(int row, int column) noexcept;

	int GetCurrentRow() { return m_CurrentRow; }
	int GetCurrentColumn() { return m_CurrentColumn; }

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
	std::weak_ptr<LevelComponent> m_pLevel{};
	int m_CurrentRow{ 1 };
	int m_CurrentColumn{ 1 };
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
};

