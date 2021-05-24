#pragma once
class ExtraMath
{
public:
	static int PyramidAmountOfBlockUntil(int row, int column) noexcept;
	static int PyramidAmountOfBlockUntilRow(int row) noexcept;
	static int PyramidGetRowFromIndex(int index) noexcept;
	static std::pair<int, int> PyramidGetCoordFromIndex(int index) noexcept;

private:
	ExtraMath();
};

