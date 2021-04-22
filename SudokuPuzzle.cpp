#include "SudokuPuzzle.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include "Cell.h"




SudokuPuzzle::SudokuPuzzle() 
{
}


void SudokuPuzzle::solve(const char filenameIn[]) {
	// Read puzzle from text file
	readPuzzle(filenameIn);

	// Get start time
	const auto startTime = std::chrono::high_resolution_clock::now();
	
	//Remove pre derived values from the all candidate lists
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			//If the value is pre given
			if (m_grid[row][column].isGiven())
			{
				Cell cell = m_grid[row][column];
				//Remove the value from that rows, columns and blocks candidate lists
				removeCandidateFromBlock(row, column,cell.getValue());
				removeCandidateFromRow(row, cell.getValue());
				removeCandidateFromColumn(column, cell.getValue());
				
			}
		
		}
	
	}
	m_loops++;

	// Game loop 
	bool solved = false;
	
	// Variables for testing performance
	while (!solved)
	{
		for (int row = 0; row < 9; row++)
		{
			solved = true;
			for (int column = 0; column < 9; column++)
			{

				//Is the cell a pre defined value
				Cell cell = m_grid[row][column];
				if (!cell.isGiven())
				{
					// is the cell solved
					if (cell.getValue() == 0)
					{
						solved = false;
						
						//Hidden single
							std::vector<int> candList = cell.getCandidateList();
							for (int i = 0; i < candList.size(); i++)
							{
									//If a candidate is the only candidate in row, block and column
								if (checkRowForHiddenSingle(row, column, candList[i]))
								{

									//Set the single as value of the cell
									m_grid[row][column].setValue(candList[i]);
									//Clear the cells candidate list
									m_grid[row][column].clearCandidateList();
									//Notify other cells of the new solved Cell
									removeCandidateFromBlock(row, column, candList[i]);
									removeCandidateFromRow(row, candList[i]);
									removeCandidateFromColumn(column, candList[i]);
									//std::cout << "Hidden single in row Found! " + std::to_string(row) + " Column: " + std::to_string(column) + "\n";
									//stop the loop
									m_cells_solved++;
									break;
								}
								  if (checkColumnForHiddenSingle(row, column, candList[i]))
								{
									//Set the single as value of the cell
									m_grid[row][column].setValue(candList[i]);
									//Clear the cells candidate list
									m_grid[row][column].clearCandidateList();
									//Notify other cells of the new solved Cell
									removeCandidateFromBlock(row, column, candList[i]);
									removeCandidateFromRow(row, candList[i]);
									removeCandidateFromColumn(column, candList[i]);
									//std::cout << "Hidden single in column Found! " + std::to_string(row) + " Column: " + std::to_string(column) + "\n";
									//stop the loop
									m_cells_solved++;
									break;
								}
								  if (checkBlockForHiddenSingle(row, column, candList[i]))
								{
									//Set the single as value of the cell
									m_grid[row][column].setValue(candList[i]);
									//Clear the cells candidate list
									m_grid[row][column].clearCandidateList();
									//Notify other cells of the new solved Cell
									removeCandidateFromBlock(row, column, candList[i]);
									removeCandidateFromRow(row, candList[i]);
									removeCandidateFromColumn(column, candList[i]);
									//std::cout << "Hidden single in BLOCK Found! " + std::to_string(row) + " Column: " + std::to_string(column) + "\n";

									m_cells_solved++;
									//stop the loop
									break;
								}
							
							}

							//Naked single
							if (cell.getCandListSize() == 1)
							{
								//std::cout << "Naked singel found !! Row: " + std::to_string(row) + " Column: " + std::to_string(column) + " Value: " + std::to_string(cell.getCandidateAt(0)) + "\n\n";
								int candidate = cell.getCandidateAt(0);

								m_grid[row][column].setValue(candidate);
								m_grid[row][column].removeCandidate(candidate);
								removeCandidateFromBlock(row, column, candidate);
								removeCandidateFromRow(row, candidate);
								removeCandidateFromColumn(column, candidate);

								m_cells_solved++;
								


							}


							
					}
				}
			}
		}
		m_loops++;
	}


	// Get end time
	const auto endTime = std::chrono::high_resolution_clock::now();
	const auto duration = (endTime - startTime).count();


	// Sample timing output in nanoseconds
	std::cout << duration << "ns" << std::endl;
	std::cout << m_loops << " loops" << std::endl;
	std::cout << m_cells_solved << " cells solved" << std::endl;
	std::cout << m_candidates_considered << " candidates considered" << std::endl;


	// Output the solved puzzle
	output();
}



void SudokuPuzzle::readPuzzle(const char filenameIn[]) 
{
	// Try to open the file
	std::ifstream inFile(filenameIn);
	if (!inFile.is_open())
		std::cerr << "File could not be opened\n";

	//
	for (int i = 0; i < 9; i++)
	{
		
		for (int y = 0; y < 9; y++)
		{
			Cell cell;
			int newValue = 0;
			inFile >> newValue;
			//If the value is 0, the cell value will be derived during solving
			if (newValue == 0)
			{
				cell = Cell(newValue, false);
			}
			else 
			{
				cell = Cell(newValue, true);
			}

			//Add the cell to the grid
			m_grid[i][y] = cell;

		}
	}

	std::cout << "File loaded\n";
}

// Check the row for a hidden single
bool SudokuPuzzle::checkRowForHiddenSingle(int row, int column, int candidate)
{
	//If any of the other cells in the row have candidate as the candidate, return false
	for (int col = 0; col < 9; col++)
	{
		if (col == column)
			continue;
		if (m_grid[row][col].isCandidate(candidate))
		{
			m_candidates_considered++;
			return false;
		}
	}

	return true;
}

// Check the column for a hidden single
bool SudokuPuzzle::checkColumnForHiddenSingle(int row, int column, int candidate)
{
	for (int i = 0; i < 9; i++)
	{
		if (row == i)
		{
			continue;
		}
		if (m_grid[i][column].isCandidate(candidate)) {
			m_candidates_considered++;

			return false;
		}
	}
	return true;
}
// Check the block for a hidden single

bool SudokuPuzzle::checkBlockForHiddenSingle(int row, int column, int candidate)
{
	int rowBlock = row / 3;
	int columnBlock = column / 3;

	int startRow = 0;
	int startColumn = 0;
	int endRow = 3;
	int endColumn = 3;
	//Calculate the starting row of the block
	if (rowBlock == 0)
	{
		//the row starts at 0
	}
	else if (rowBlock == 1)
	{
		//The row starts at 3
		startRow += 3;
		endRow = startRow + 3;
	}
	else
	{
		//The row starts at 6
		startRow += 6;
		endRow = startRow + 3;
	}

	if (columnBlock == 0)
	{
		//the column starts at 0
	}
	else if (columnBlock == 1)
	{
		//The column starts at 3
		startColumn += 3;
		endColumn = startColumn + 3;
	}
	else
	{
		//The column starts at 6
		startColumn += 6;
		endColumn = startColumn + 3;
	}

	//Remove candidate from the block
	for (int i = startRow; i < endRow; i++)
	{
		for (int y = startColumn; y < endColumn; y++)
		{
			if (i == row && y == column)
			{
				continue;
			}
			//only remove the candidate if the value is 0 (not solved yet)
			if (m_grid[i][y].isCandidate(candidate))
			{
				m_candidates_considered++;

				return false;
			}
		}
	}

	return true;
}

// Remove the candidate from all cells in the row

void SudokuPuzzle::removeCandidateFromRow(int row, int candidate)
{
	//Loop through the row and remove candidate from each cell
	for (int col = 0; col < 9; col++)
	{
		m_grid[row][col].removeCandidate(candidate);
	}
}
// Remove the candidate from all cells in the column
void SudokuPuzzle::removeCandidateFromColumn(int column, int candidate)
{
	for (int row = 0; row < 9; row++)
	{
		m_grid[row][column].removeCandidate(candidate);
	}
}

// Remove the candidate from all cells in the block
void SudokuPuzzle::removeCandidateFromBlock(int row, int column, int candidate)
{
	

	int rowBlock = row / 3;
	int columnBlock = column / 3;
	int startRow = 0;
	int startColumn = 0;
	int endRow = 3;
	int endColumn = 3;

	//Calculate the starting row of the block
	if (rowBlock == 0)
	{
		//the row starts at 0
	}
	else if (rowBlock == 1)
	{
		//The row starts at 3
		startRow += 3;
		endRow = startRow + 3;
	}
	else 
	{
		//The row starts at 6
		startRow += 6;
		endRow = startRow + 3;
	}

	if (columnBlock == 0)
	{
		//the column starts at 0
	}
	else if (columnBlock == 1)
	{
		//The column starts at 3
		startColumn += 3;
		endColumn = startColumn + 3;
	}
	else
	{
		//The column starts at 6
		startColumn += 6;
		endColumn = startColumn + 3;
	}

	//Remove candidate from the block
	for (int i = startRow; i < endRow; i++)
	{
		for (int y = startColumn; y < endColumn; y++)
		{
			
			//only remove the candidate if the value is 0 (not solved yet)
			if (m_grid[i][y].getValue() == 0)
			{
				m_grid[i][y].removeCandidate(candidate);
				//std::cout << "Candidate " + std::to_string(candidate) << " removed  from Row: " + std::to_string(i) << " Column:" + std::to_string(y) << "\n";
			}
		}
	}
}


void SudokuPuzzle::output() const {
	// Add code to output your solved puzzle
	std::ofstream outFile;
	outFile.open("sudoku_solution.txt");
	if (!outFile.is_open())
	{
		std::cerr << "Output file could not be opened/created";
	}


	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			const Cell newInt = m_grid[row][col];
			outFile << newInt.getValue() << ' ';
			std::cout << newInt.getValue() << ' ';
		}
		outFile << '\n';
		std::cout << '\n';
	}
}