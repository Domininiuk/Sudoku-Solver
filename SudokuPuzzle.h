#pragma once
#include "Cell.h"
// Add your code here

class SudokuPuzzle 
{
public:
	SudokuPuzzle();

	void solve (const char filenameIn[]);

	// Add your code here

private:
	void output() const;

	void readPuzzle(const char filenameIn[]);
	void removeCandidateFromRow(int row, int candidate);
	void removeCandidateFromColumn(int column, int candidate);
	void removeCandidateFromBlock(int row, int column, int candidate);
	bool checkRowForHiddenSingle(int row, int column, int candidate);
	bool checkColumnForHiddenSingle(int row, int column, int candidate);
	bool checkBlockForHiddenSingle(int row, int column, int candidate);
	// Add your code here

	Cell m_grid[9][9];
};