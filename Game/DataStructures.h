#pragma once


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
	BlockComponent* blockTouched = nullptr;
	bool blockOccupied = false;
	bool didMove = false;
	bool validMove = false;
};