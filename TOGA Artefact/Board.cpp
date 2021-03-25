#include "Board.h"
#include "Macros.h"
#include "textHandling.h"

#include <iostream>
#include <string>
#include <conio.h>

#include <vector>
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
			ships_ptr[i - 3].hits = 0;
			break;
		case 4:
			ships_ptr[i - 3].name = "Battleship";
			ships_ptr[i - 3].length = 4;
			ships_ptr[i - 3].hits = 0;
			break;
		case 3:
			ships_ptr[i - 3].name = "Cruiser";
			ships_ptr[i - 3].length = 3;
			ships_ptr[i - 3].hits = 0;
			break;
		case 2:
			ships_ptr[i - 3].name = "Destroyer";
			ships_ptr[i - 3].length = 2;
			ships_ptr[i - 3].hits = 0;
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
	consoleCursorVisible(false);

	// Top axis
	for (int x = 0; x < (3 * board_size); x += 3) {
		setCursorPosition(x+11, 4);
		char c = x/3; // divide to compensate for loop steps
		c = c + 'A'; // numeric value -> alpha value
		std::cout << c;
	}	

	// Left axis
	for (int y = 0; y < board_size; y++) {			//  8	print numbers
		setCursorPosition((y<10) ? 7 : 6, y + 6);	//  9   from right
		std::cout << y;								// 10   to left
	}												// 11

	for (int x = 0; x < (3*board_size); x+= 3) {
		for (int y = 0; y < board_size; y++) {
			setCursorPosition(x + 11, y + 6);
			std::cout << grid[y][x/3];
		}
	}
	consoleCursorVisible(true);
}

void Board::placeShips() {
	std::string firstLine = "Place down your "; // If this line changes I won't have to change it in 2 places, as it's used at the bottom of the first for loop

	std::cout << firstLine << "Carrier\n";
	std::cout << "Arrow keys to move, R to rotate\n";
	std::cout << "Press enter to lock the ship in place\n\n";

	for (int i = 0; i < numOfShips; i++) {
		short x = 0;
		short y = 0;
		bool hor = true;
		bool placed = false;

		int shipLength = ships_ptr[i].length;

		for (int j = x; j < shipLength; j++) {
			Draw(j, y, (grid[y][j] == SHIP) ? HIT : SHIP);
		}

		while(!placed) {
			
			displayBoard();

			setCursorPosition(0, board_size + 6);
			std::cout << x<< y;

			char c = _getch();
			if (c == -32) {
				// Arrow keys

				c = _getch();
				switch (c) {
				case 72:	// UP_key
					if (y > 0) {
						y -= 1;
						if (hor) {
							for (int j = x; j < (x + shipLength); j++) {
								Draw(j, y + 1, (grid[y + 1][j] == HIT) ? SHIP : WATER);
								Draw(j, y, (grid[y][j] == SHIP) ? HIT : SHIP);
							}
						}
						else {
							Draw(x, y, (grid[y][x] == SHIP) ? HIT : SHIP);
							Draw(x, y + shipLength, (grid[y + shipLength][x] == HIT) ? SHIP : WATER);
						}
					}
					break;

				case 80:	// DOWN_key
					if (hor) {
						if (y < board_size - 1) {
							y += 1;
							for (int j = x; j < (x + shipLength); j++) {
								Draw(j, y - 1, (grid[y - 1][j] == HIT) ? SHIP : WATER);
								Draw(j, y, (grid[y][j] == SHIP) ? HIT : SHIP);
							}
						}
					}
					else {
						if (y < board_size - (shipLength)) {
							y += 1;
							Draw(x, y - 1, (grid[y - 1][x] == HIT) ? SHIP : WATER);
							Draw(x, y + shipLength - 1, (grid[int(y) + shipLength - 1][x] == SHIP) ? HIT : SHIP);
						}
					}
					break;

				case 75:	// LEFT_key
					if (x > 0) {
						x -= 1;
						if (hor) {
							Draw(x, y, (grid[y][x] == SHIP) ? HIT : SHIP);
							Draw(x + shipLength, y, (grid[y][x + shipLength] == HIT) ? SHIP : WATER);
						}
						else { // vertical
							for (int j = y; j < (y + shipLength); j++) {
								Draw(x + 1, j, (grid[j][x+1] == HIT) ? SHIP : WATER);
								Draw(x, j, (grid[j][x] == SHIP) ? HIT : SHIP);
							}
						}
					}
					break;

				case 77:	// RIGHT_key
					if (hor) { // horizontal
						if (x < board_size - (shipLength)) {
							x += 1;
							Draw(x - 1, y, (grid[y][x-1] == HIT) ? SHIP : WATER);
							Draw(x + shipLength - 1, y, (grid[y][x + shipLength - 1] == SHIP) ? HIT : SHIP);
						}
					}
					else { // vertical
						if (x < board_size - 1) {
							x += 1;
							for (int j = y; j < (y + shipLength); j++) {
								Draw(x - 1, j, (grid[j][x-1] == HIT) ? SHIP : WATER);
								Draw(x, j, (grid[j][x] == SHIP) ? HIT : SHIP);
							}
						}
					}
					break;
				}

			}
			else {
				// Normal characters
				switch (c) {
				case 'r':
					if (hor) { // horizontal
						hor = false;
						for (int j = (x); j < x + shipLength; j++) {
							Draw(j, y, (grid[y][j] == HIT) ? SHIP : WATER);
						}
						if (y > board_size - (shipLength)) {
							y -= (shipLength - (board_size - y));
						}
						for (int j = (y); j < y + shipLength; j++) {
							Draw(x, j, (grid[j][x] == SHIP) ? HIT : SHIP);
						}
					}
					else { // vertical
						hor = true;
						for (int j = (y); j < y + shipLength; j++) {
							Draw(x, j, (grid[j][x] == HIT) ? SHIP : WATER);
						}
						if (x >= board_size - (shipLength - 1)) {
							x -= (shipLength - (board_size - x));
						}
						for (int j = (x); j < x + shipLength; j++) {
							Draw(j, y, (grid[y][j] == SHIP) ? HIT : SHIP);
						}
					}
					break;
				case 13:
					bool valid = true;
					for (int row = 0; row < board_size; row++) {
						for (int col = 0; col < board_size; col++) {
							if (grid[row][col] == HIT) { valid = false; }
						}
					}
					if (valid) {
						if (hor) {
							for (int j = 0; j < shipLength; j++) {
								ships_ptr[i].coordinates.push_back(std::make_tuple(x + j, y));
							}
						}
						else {
							for (int j = 0; j < shipLength; j++) {
								ships_ptr[i].coordinates.push_back(std::make_tuple(x, y + j));
							}
						}
						x = 0; y = 0;
						placed = true;
					}
					break;
				}
			}
		}
		setCursorPosition(firstLine.length(), 0);
		std::cout << ships_ptr[i + 1].name << "      "; // 
	}
}

void Board::Draw(int col, int row, char newElement) {
	grid[row][col] = newElement;
}
