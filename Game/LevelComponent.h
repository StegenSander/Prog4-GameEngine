#pragma once
#include "BaseComponent.h"
#include "Listener.h"

enum class EntityType
{
	QBert,
	Coily,
	UggAndWrongway,
	SlickAndSam,
};
class BlockComponent;
class GameControllerComponent;
class LevelComponent
	: public BaseComponent
	, public Listener
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	LevelComponent(int rows, int blockSize,const std::weak_ptr<GameControllerComponent>& pGameController);
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
	void PlayerDamaged();

	void Notify(EventType type, EventData* eventData) override;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------ 	
private:
	//------PRIVATE FUNCTIONS------
	void CreateColorCube(const std::pair<int,int>& rowColumn, const glm::vec3& pos);
	void CreateVoidBLock(const std::pair<int, int>& rowColumn, const glm::vec3& pos);

	//------PRIVATE VARIABLES------	
	int m_Rows;
	int m_BlockSize;
	std::vector<std::shared_ptr<BlockComponent>> m_Level;
	std::weak_ptr<GameControllerComponent> m_pGameController;
};

