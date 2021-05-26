#pragma once
class ExtraMath
{
public:
	static int PyramidAmountOfBlockUntil(int row, int column) noexcept;
	static int PyramidAmountOfBlockUntilRow(int row) noexcept;
	static int PyramidGetRowFromIndex(int index) noexcept;
	//return pair<Row,Column>
	static std::pair<int, int> PyramidGetCoordFromIndex(int index) noexcept;

	static float RandomFloat(int min, int max, int precision = 1000);

private:
	ExtraMath();
};

