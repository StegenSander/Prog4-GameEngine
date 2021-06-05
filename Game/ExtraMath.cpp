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

int ExtraMath::DistanceFromTo(int row1, int column1, int row2, int column2)
{
	int moves = 0;

	//move from start point to end point and count the moves
	while (row1 != row2 || column1 != column2)
	{
		int rowDiff = row2 - row1;
		int columnDiff = column2 - column1;
		moves++;

		if (columnDiff == 0 && rowDiff < 0) // Northeast Move
		{
			row1--; 
			continue;
		}
		if (columnDiff == 0 && rowDiff > 0) // SoutWest Move
		{
			row1++;
			continue;
		}
		if (rowDiff <= 0 && columnDiff > 0) //NorthEast move
		{
			row1--;
			continue;
		}
		 if (rowDiff <= 0 && columnDiff < 0) //NorthWest move
		{
			row1--;
			column1--;
			continue;
		}
		if (rowDiff > 0 && columnDiff > 0) //SouthEast move
		{
			row1++;
			column1++;
			continue;
		}
		if (rowDiff > 0 && columnDiff < 0) // SouthWest moves
		{
			row1++;
			continue;
		}
	}

	return moves;
}

float ExtraMath::RandomFloat(int min, int max, int precision)
{
	return	(rand() % ((max - min) * precision)) / static_cast<float>(precision) + min;
}
