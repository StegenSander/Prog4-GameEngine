#pragma once
#include "Transform.h"


enum class Direction
{
	NorthEast,
	SouthEast,
	SouthWest,
	NorthWest,
};
enum class BlockSide
{
	Top,
	Left,
	Right,
};

enum class EntityType
{
	QBert,
	Coily,
	UggAndWrongway,
	SlickAndSam,
};

class EntityComponent;
struct EntityInfo
{
	EntityType Type = EntityType::QBert;
	EntityComponent* Behaviour = nullptr;
};

class BlockComponent;
struct MoveResult
{
	BlockComponent* BlockTouched = nullptr;
	bool BlockOccupied = false;
	bool DidMove = false;
	bool ValidMove = false;
};

struct GameRules
{
	int AmountOfColorChanges{};
	bool Revertible{};
};

struct LevelData
{
	int LevelSize{};
	int RowOfDiscs{};
	glm::vec3 LevelPosition{};
};

struct QBertData
{
	int Lives{};
	float TimeBetweenMoves{};
};

struct EntityData
{
	int MaxEntitiesAlive{};
	int MinSpawnDuration{};
	int MaxSpawnDuration{};
	float TimeBetweenMoves{};
};