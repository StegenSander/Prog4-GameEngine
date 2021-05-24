#include "MiniginPCH.h"
#include "ExtraMath.h"

int ExtraMath::PyramidAmountOfBlockUntil(int row, int column)noexcept
{
    return PyramidAmountOfBlockUntilRow(row) + column;
}

int ExtraMath::PyramidAmountOfBlockUntilRow(int row) noexcept
{
	if (row > 1)
	{
		return row + PyramidAmountOfBlockUntilRow(row-1);
	}
	return row;
}

int ExtraMath::PyramidGetRowFromIndex(int index) noexcept
{
	index += 1;
	int row = 1;
	while (true)
	{
		index -= row;
		if (index > 0) row++;
		else return row;
	}
}

std::pair<int, int> ExtraMath::PyramidGetCoordFromIndex(int index) noexcept
{
	index += 1;
	int row = 1;
	while (true)
	{
		index -= row;
		if (index > 0) row++;
		else return std::pair<int,int>(row,index + row);
	}
}
