#pragma once
#include "BaseComponent.h"

enum class EntityType
{
	QBert,
	UggAndWrongway,
	SlickAndSam,
};
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

	std::weak_ptr<BlockComponent> GetBlockAtIndex(int index);
	size_t AmountOfBlocks() { return m_Level.size(); }
	int AmountOfRows() { return m_Rows; }
	void BlockTouched(int row, int column, EntityType type);
	void BlockTouched(int index, EntityType type);
	bool IsLevelFinished();

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

