#include "SudokuPuzzle.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include "Cell.h"


SudokuPuzzle::SudokuPuzzle() 
{
	// Add code to initialise the SudokuPuzzle object
}


void SudokuPuzzle::solve(const char filenameIn[]) {
	// Read puzzle from text file
	readPuzzle(filenameIn);

	// Get start time
	const auto startTime = std::chrono::high_resolution_clock::now();

	// Add code to solve the puzzle


	//Keep going through every cell on the board until 


	//I think last sudoku didnt notify others cells when a cell was solved, which caused problems


	//Remove pre derived valeus from the all candidate lists and then start teh main game loop?
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			//If the value is pre given
			if (m_grid[row][column].isGiven())
			{
				if (row == 2 && column == 7)
				{
					int debug = -1;
				}
				Cell cell = m_grid[row][column];
				//Remove the value from that rows, columns and blocks candidate lists
				removeCandidateFromBlock(row, column,cell.getValue());
				removeCandidateFromRow(row, cell.getValue());
				removeCandidateFromColumn(column, cell.getValue());
				
			}
		}
	}
	//row 0 col 6 wrong solved
	//row 2  col 7 candidate not removed correctly
	// Game loop 
	bool solved = false;
	int temp = 20;
	while (temp)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int column = 0; column < 9; column++)
			{
				if (row == 0 && column == 6)
				{
					int d = -1;
				}

				//Is the cell pre derived
				Cell cell = m_grid[row][column];
				if (!cell.isGiven())
				{
					// is the cell solved
					if (cell.getValue() == 0)
					{
						
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
									std::cout << "Hidden single in row Found! " + std::to_string(row) + " Column: " + std::to_string(column) + "\n";
									//stop the loop
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
									std::cout << "Hidden single in column Found! " + std::to_string(row) + " Column: " + std::to_string(column) + "\n";
									//stop the loop
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
									std::cout << "Hidden single in BLOCK Found! " + std::to_string(row) + " Column: " + std::to_string(column) + "\n";
									//stop the loop
									break;
								}
							
							}

							//Naked single
							if (cell.getCandListSize() == 1)
							{
								std::cout << "Naked singel found !! Row: " + std::to_string(row) + " Column: " + std::to_string(column) + " Value: " + std::to_string(cell.getCandidateAt(0)) + "\n\n";
								int candidate = cell.getCandidateAt(0);

								m_grid[row][column].setValue(candidate);
								m_grid[row][column].removeCandidate(candidate);
								removeCandidateFromBlock(row, column, candidate);
								removeCandidateFromRow(row, candidate);
								removeCandidateFromColumn(column, candidate);



							}
							


							//The hidden single implementation is bugged
							//The value is a hidden signle only  if its the only candidate of that value appearing  in row, column, and block
							//Think there is something wrong with the blocks idk
							
							
						
					}
				}
			}
		}
		temp--;
	}


	// Get end time
	const auto endTime = std::chrono::high_resolution_clock::now();
	const auto duration = (endTime - startTime).count();

	// Sample timing output in nanoseconds
	std::cout << duration << "ns" << std::endl;

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

bool SudokuPuzzle::checkRowForHiddenSingle(int row, int column, int candidate)
{
	//If any of the other cells in the row have candidate as the candidate, return false
	for (int col = 0; col < 9; col++)
	{
		if (col == column)
			continue;
		if (m_grid[row][col].isCandidate(candidate))
		{
			return false;
		}
	}

	return true;
}
bool SudokuPuzzle::checkColumnForHiddenSingle(int row, int column, int candidate)
{
	for (int i = 0; i < 9; i++)
	{
		if (row == i)
		{
			continue;
		}
		if (m_grid[i][column].isCandidate(candidate)) {
			return false;
		}
	}
	return true;
}
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
				return false;
			}
		}
	}

	return true;
}
void SudokuPuzzle::removeCandidateFromRow(int row, int candidate)
{
	//Loop through the row and remove candidate from each cell
	for (int col = 0; col < 9; col++)
	{
		m_grid[row][col].removeCandidate(candidate);
	}
}

void SudokuPuzzle::removeCandidateFromColumn(int column, int candidate)
{
	for (int row = 0; row < 9; row++)
	{
		m_grid[row][column].removeCandidate(candidate);
	}
}

void SudokuPuzzle::removeCandidateFromBlock(int row, int column, int candidate)
{
	
	//Need the values for row and column so I can loop through the block and remove candidates
	//Try to round up to the nearest multiple of 3 (each block has 3 columns and 3 rows)? 

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