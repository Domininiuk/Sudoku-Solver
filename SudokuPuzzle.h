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
	int m_loops = 0;
	int m_cells_solved = 0;
	int m_candidates_considered = 0;

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