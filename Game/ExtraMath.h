#pragma once
class ExtraMath
{
public:
	ExtraMath() = delete;
	static int PyramidAmountOfBlockUntil(int row, int column) noexcept;
	static int PyramidAmountOfBlockUntilRow(int row) noexcept;
	static int PyramidGetRowFromIndex(int index) noexcept;
	//return pair<Row,Column>
	static std::pair<int, int> PyramidGetCoordFromIndex(int index) noexcept;

	static int DistanceFromTo(int row1, int column1, int row2, int column2);

	static float RandomFloat(int min, int max, int precision = 1000);
};

