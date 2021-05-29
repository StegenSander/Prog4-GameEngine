#pragma once
#include "LevelNavigatorComponent.h"

class UandWLevelNavigatorComponent final
	:public LevelNavigatorComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	UandWLevelNavigatorComponent(const std::weak_ptr<LevelComponent>& pLevel, BlockSide blockside);
	virtual ~UandWLevelNavigatorComponent();

	//------COPY CONSTRUCTORS------
	UandWLevelNavigatorComponent(const UandWLevelNavigatorComponent&) = delete;
	UandWLevelNavigatorComponent(UandWLevelNavigatorComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	UandWLevelNavigatorComponent operator=(const UandWLevelNavigatorComponent&) = delete;
	UandWLevelNavigatorComponent& operator=(UandWLevelNavigatorComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	MoveResult MoveToSquare(int row, int column, EntityComponent* entityComp) override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	BlockSide m_BlockSide;
};

