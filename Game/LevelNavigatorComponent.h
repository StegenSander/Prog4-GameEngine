#pragma once
#include "BaseComponent.h"
#include "DataStructures.h"

class LevelComponent;
class BlockComponent;
class EntityComponent;
class LevelNavigatorComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	LevelNavigatorComponent(const std::weak_ptr<LevelComponent>& pLevel, BlockSide blockside = BlockSide::Top);
	virtual ~LevelNavigatorComponent();

	//------COPY CONSTRUCTORS------
	LevelNavigatorComponent(const LevelNavigatorComponent&) = delete;
	LevelNavigatorComponent(LevelNavigatorComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	LevelNavigatorComponent operator=(const LevelNavigatorComponent&) = delete;
	LevelNavigatorComponent& operator=(LevelNavigatorComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	//Return if move was successful or not
	virtual MoveResult MoveToSquare(int row, int column, EntityComponent* entityComp);
	//Return if move was successful or not
	MoveResult MoveToSquare(int index, EntityComponent* entityComp);
	//Return if move was successful or not
	MoveResult Move(Direction dir, EntityComponent* entityComp);

	void Update() override {};
	bool IsValidPyramidCoord(int row, int column) const noexcept;

	int GetCurrentRow() const { return m_CurrentRow; }
	int GetCurrentColumn() const { return m_CurrentColumn; }

	void UnRegisterFromBlock() const;
	void RegisterOnBlock(EntityComponent* entityComp) const;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------
	std::weak_ptr<BlockComponent> GetCorrectBlockAt(int row, int column) const;

	//------PROTECTED VARIABLES------	
	std::weak_ptr<LevelComponent> m_pLevel{};
	int m_CurrentRow{ 1 };
	int m_CurrentColumn{ 1 };
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	BlockSide m_BlockSide;
};

