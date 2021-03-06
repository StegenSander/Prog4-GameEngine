#pragma once
#include "BaseComponent.h"
#include "Listener.h"

class BlockComponent;
class GameControllerComponent;
struct EntityInfo;
class LevelComponent
	: public BaseComponent
	, public Listener
{
public:
	//------CONSTRUCTOR/DESTRUCTOR------
	LevelComponent(int rows, int blockSize, int discRow
		,const std::weak_ptr<GameControllerComponent>& pGameController
		, int maxColorLeverl, bool revertible);
	virtual ~LevelComponent() = default;

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
	void SetBlockToVoid(int row, int column);
	void SetBlockToDisc(int row, int column);

	void InitializeDiscs(int row);

	void BlockTouched(int row, int column, const EntityInfo& info);
	void BlockTouched(int index,const EntityInfo& info);

	bool IsLevelFinished();
	void PlayerDamaged() const;
	void PlayerFallen() const;

	void Notify(EventType type, EventData* eventData) override;

	void HandleCollision(const EntityInfo& firstObject, const EntityInfo& secondObject) const;

	//------PUBLIC VARIABLES------
protected:
	//------PROTECTED FUNCTIONS------

	//------PROTECTED VARIABLES------ 	
private:
	//------PRIVATE FUNCTIONS------
	void CreateColorCube(const std::pair<int,int>& rowColumn, const glm::vec3& pos);
	void CreateVoidBlock(const std::pair<int, int>& rowColumn, const glm::vec3& pos);
	void CreateDisc(const std::pair<int, int>& rowColumn, const glm::vec3& pos);
	void LevelFinished();
	void FullReset();

	//------PRIVATE VARIABLES------	
	int m_Rows;
	int m_BlockSize;
	int m_DiscRow;
	int m_MaxColorLevel;
	std::vector<std::shared_ptr<BlockComponent>> m_Level;
	std::weak_ptr<GameControllerComponent> m_pGameController;
	bool m_Revertible;
};

