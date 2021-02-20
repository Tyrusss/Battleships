#include "Board.h"
#include "Macros.h"

#include <iostream>
#include <string>

Board::Board(int size) {

	board_size = size;

	if (board_size >= 100) { board_size = 75; }

	initBoard();
}

void Board::initBoard() {

	std::vector<char> tempVect;
	for (int row = 0; row < board_size; row++) {	// tempVect = { '~', '~', '~', ... }
		tempVect.push_back(WATER);
	}
													// grid =	{
	for (int row = 0; row < board_size; row++) {	//				{ '~', '~', '~', ... },
		grid.push_back(tempVect);					//				{ '~', '~', '~', ... },
	}												//				...
													//			}
}

void Board::displayBoard() {

	std::cout << "\n"; //newline

	bool firstRowDisplayed = false;
	std::string rowStr;

	std::string firstRowStr = (board_size < 10) ? ("\t") : ("\t "); // If there are two digit numbers then make sure the grid isn't offset
	std::cout << firstRowStr;

	for (int row = 0; row < board_size + 1; row++) {

		if (firstRowDisplayed) {
			rowStr = (row < 10) ? ("\t" + std::to_string(row) + "  ") : ("\t" + std::to_string(row) + " "); 
		}
		else {
			rowStr = (row < 10) ? ("  ") : (" ");
		}
		std::cout << rowStr;

		for (int col = 0; col < board_size; col++) {

			if (!firstRowDisplayed) {
				std::string oneDigit;
				oneDigit = (col < 9) ? std::to_string(col + 1) + "  " : std::to_string(col + 1) + " ";
				std::cout << oneDigit;
			} else {
				std::cout << grid[row - 1][col] << "  ";
			}
		}
		firstRowDisplayed = true;
		std::cout << "\n";
	}
}

void Board::placeShip(int shipSize) {

}

void Board::Draw(int col, int row, char newElement) {
	grid[row][col] = newElement;
}