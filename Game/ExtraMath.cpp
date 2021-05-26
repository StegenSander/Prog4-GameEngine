#include "MiniginPCH.h"
#include "ExtraMath.h"

int ExtraMath::PyramidAmountOfBlockUntil(int row, int column)noexcept
{
    return PyramidAmountOfBlockUntilRow(row-1) + column-1;
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

float ExtraMath::RandomFloat(int min, int max, int precision)
{
	return	(rand() % ((max - min) * precision)) / float(precision) + min;
}
