#pragma once
#include "BaseComponent.h"

class BlockComponent;
class LevelComponent
	: public BaseComponent
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	LevelComponent(int rows, int blockSize);
	virtual ~LevelComponent();

	//------COPY CONSTRUCTORS------
	LevelComponent(const LevelComponent&) = delete;
	LevelComponent(LevelComponent&&) = delete;
	//------ASSIGNMENT OPERATORS------
	LevelComponent operator=(const LevelComponent&) = delete;
	LevelComponent& operator=(LevelComponent&&) = delete;

	//------PUBLIC FUNCTIONS------
	void Update() override;

	//Object must be part of a scene before calling this function
	void CreateLevel();

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------ 	
private:
	//------PRIVATE FUNCTIONS------

	//------PRIVATE VARIABLES------	
	int m_Rows;
	int m_BlockSize;
	std::vector<std::shared_ptr<BlockComponent>> m_Level;
};

