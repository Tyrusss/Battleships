#include "Board.h"
#include "Macros.h"

#include <iostream>
#include <string>
#include <tuple>

Board::Board(int size) { // constructor

	board_size = size;

	if (board_size > 25) { board_size = 25; }
	else if (board_size < 6) { board_size = 6; }

	numOfShips = board_size - 4;	// The number of ships on the grid is calculated by adding one ship
									// for every row on the board, from a default of two ships on a board_size of 6.
									// The size of the ships is a decremental loop from 5 to 2.

									// e.g. for a board_size 10 there will be six ships,
									// two size 5 ships, two size 4 ships, one size 3 ship, and one size 2 ship.

	ships_ptr = new Ship[numOfShips];

	int temp;
	for (int i = 3; i < numOfShips + 3; i++) {
		temp = (((i * 3) + 2) % 4) + 2;			// closed function for above repeating pattern (5,4,3,2,5,4,3,2,5,4,...)

		switch (temp) {
		case 5:
			ships_ptr[i - 3].name = "Carrier";
			ships_ptr[i - 3].length = 5;
			break;
		case 4:
			ships_ptr[i - 3].name = "Battleship";
			ships_ptr[i - 3].length = 4;
			break;
		case 3:
			ships_ptr[i - 3].name = "Cruiser";
			ships_ptr[i - 3].length = 3;
			break;
		case 2:
			ships_ptr[i - 3].name = "Destroyer";
			ships_ptr[i - 3].length = 2;
			break;
		default:
			std::cout << "uh oh, you br0ke it";
			break;
		}
	}
	initBoard();
}

Board::~Board() { delete[] ships_ptr; } // destructor

void Board::initBoard() {

	grid.clear(); // Set the container size to 0

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

	std::string gridStr;

	for (int row = 0; row < (board_size + 1) ; row++) {

		gridStr += "\t";
		if (row != 0) { gridStr += (row < 10) ? std::to_string(row) + "  " : std::to_string(row) + " "; }	// y coords
		else { gridStr += "   "; }

		for (int col = 0; col < board_size; col++) {
			if (row == 0) {
				gridStr += (col < 9) ? std::to_string(col + 1) + "  " : std::to_string(col + 1) + " ";		// x coords
			}
			else {
				gridStr += grid[row - 1][col];
				gridStr += "  ";
			}
		}
		gridStr += "\n";
	}
	std::cout << gridStr;
}

void Board::placeShips() {

	for (int i = 0; i < numOfShips; i++) {


	}

	//int startCoord[2];	// The point at which the ship will start
	//std::string dir;	// The direction of the ship
	//char xy;
	//
	//for (;;) { // input validation
	//	for (int coord = 0; coord < 2; coord++) {

	//		xy = (coord == 0) ? 'x' : 'y';
	//		for (;;) {
	//			std::cout << "Which " << xy << " coordinate do you want the ship to start in?\n";

	//			if (std::cin >> startCoord[coord]			// input must be int
	//				&& startCoord[coord] <= board_size		// must be <= board_size
	//				&& startCoord[coord] >= 1	 			// must be >= 1 
	//				)
	//			{
	//				break;
	//			}

	//			else {
	//				std::cout << "Please enter a valid coordinate (1 - " << board_size << ")" << std::endl;
	//				std::cin.clear();
	//				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//			}
	//		}
	//	}

	//	std::cout << "The front of the ship will be at (" << startCoord[0] << "," << startCoord[1] << ")";

	//	std::tuple<int, int> returnDir;

	//	for (;;) {
	//		std::cout << "\nDo you want the ship to continue UP, RIGHT, DOWN, LEFT, or do you want to RESTART by re-entering the start coordinates?\n";

	//		if (std::cin >> dir) {

	//			if (dir == "UP") // if only switch worked with str
	//			{
	//				returnDir = std::make_tuple(0, -1);
	//				return returnDir;
	//			}
	//			if (dir == "RIGHT") {
	//				returnDir = std::make_tuple(1, 0);
	//				return returnDir;
	//			}
	//			if (dir == "LEFT") {
	//				returnDir = std::make_tuple(-1, 0);
	//				return returnDir;
	//			}
	//			if (dir == "DOWN") {
	//				returnDir = std::make_tuple(0, 1);
	//				return returnDir;
	//			}
	//			if (dir == "RESTART") {
	//				break;
	//			}
	//		}
	//		else { std::cout << "Please enter a valid response"; }
	//	}
	//}
}

void Board::Draw(int col, int row, char newElement) {
	grid[row][col] = newElement;
}
