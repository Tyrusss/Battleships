#include "Board.h"
#include "Macros.h"
#include "textHandling.h"

#include <iostream>
#include <string>
#include <conio.h>
//#include <stdlib.h>

#include <vector>
#include <tuple>

Board::Board(int size) { // constructor

	board_size = size;

	// Clamping
	if (board_size > 25) { board_size = 25; }
	else if (board_size < 6) { board_size = 6; }

	numOfShips = board_size - 4;	// The number of ships on the grid is calculated by adding one ship
									// for every row on the board, from a default of two ships on a board_size of 6.
									// The size of the ships is a decremental loop from 5 to 2.

									// e.g. for a board_size 10 there will be six ships,
									// two size 5 ships, two size 4 ships, one size 3 ship, and one size 2 ship.

	ships_ptr = new Ship[numOfShips]; // Dynamic array declaration (deleted in destructor)

	int temp;
	for (int i = 3; i < numOfShips + 3; i++) {

		// Closed function for above repeating pattern (5,4,3,2,5,4,3,2,5,4,...)
		temp = (((i * 3) + 2) % 4) + 2;

		// Initialise array of ships with name, length, and hits
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
	for (int x = 0; x < (3 * board_size); x += 3) { // Step by 3 to space out rows and columns evenly
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

	// Main grid
	for (int x = 0; x < (3*board_size); x+= 3) {
		for (int y = 0; y < board_size; y++) {
			setCursorPosition(x + 11, y + 6); // offset grid position for aesthetics
			std::cout << grid[y][x/3];
		}
	}
	consoleCursorVisible(true);
}

void Board::placeShips() {
	std::string firstLine = "Place down your "; // If this line changes I won't have to change it in 2 places, as it's used at the bottom of the for loop

	setCursorPosition(0, 0);

	std::cout << firstLine << "Carrier\n";
	std::cout << "Arrow keys to move, R to rotate\n";
	std::cout << "Press enter to lock the ship in place\n\n";

	for (int i = 0; i < numOfShips; i++) {
		short x = 0;
		short y = 0;
		bool hor = true; // If the ship is currently horizontal
		bool placed = false; // If it has been placed down

		int shipLength = ships_ptr[i].length;

		// If the ship is being drawn over the top of a ship that has been placed
		// down, then draw the spaces as crosses. If there is no overlap, then draw
		// the spaces as S's

		// Draw the ship in the top left corner to begin
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

				c = _getch(); // Arrow keys require a second getch_() call
				switch (c) {
				case 72:	// UP_key moves the ship up

					// Don't move the ship if it's at the top of the grid
					if (y > 0) { 

						// Move y upwards
						y -= 1; 

						// If the ship is horizontal
						if (hor) {
							for (int j = x; j < (x + shipLength); j++) {					// move each
								Draw(j, y + 1, (grid[y + 1][j] == HIT) ? SHIP : WATER);		// point
								Draw(j, y, (grid[y][j] == SHIP) ? HIT : SHIP);				// upwards once
							}
						}

						// If the ship is vertical
						else { 

							// Draw a space above the top
							Draw(x, y, (grid[y][x] == SHIP) ? HIT : SHIP);

							// Remove the space at the bottom
							Draw(x, y + shipLength, (grid[y + shipLength][x] == HIT) ? SHIP : WATER);
						}
					}
					break;

				case 75:	// LEFT_key moves the ship left
					if (x > 0) {// Don't move the ship if it's at the left of the grid
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

				case 77:	// RIGHT_key moves the ship right
					if (hor) { // horizontal
						if (x < board_size - (shipLength)) { // Don't move the ship if it's at the right of the grid
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

				case 80:	// DOWN_key moves the ship down
					if (hor) {
						if (y < board_size - 1) { // Don't move the ship if it's at the bottom of the grid
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
				}

			}
			else {
				// Normal characters
				switch (c) {
				case 'r': // r rotates the ship
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
				case 13: // enter locks the ship in place
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
		if (i < numOfShips - 1) {
			setCursorPosition(firstLine.length(), 0);
			std::cout << ships_ptr[i + 1].name << "      "; // overwrite ship name with next ship 
		}
	}
}


void Board::Draw(int col, int row, char newElement) {
	grid[row][col] = newElement;
}

//EnemyBoard::EnemyBoard(int size) : Board{ size } {
//	placeShips();
//}
//
//void EnemyBoard::placeShips() {
//
//	int x;
//	int y;
//
//	setCursorPosition(0, board_size + 8);
//	
//	for (int i = 0; i < numOfShips; i++) {
//		for (int j = 0; j < ships_ptr[i].coordinates.size(); j++) {
//
//			
//
//		}
//
//	}
//
//}
