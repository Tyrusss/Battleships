#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include <string>
#include <tuple>

struct Ship; // forward declaration

class Board {

public:
	void initBoard();
	void displayBoard();
	void placeShips();

	Board(int size);
	~Board();

private:
	int board_size;							// size of the grid (board_size 10 gives a 10x10 grid)
	std::vector<std::vector<char>> grid;	// 2D vector containing the grid spaces
	
	int numOfShips;

	Ship* ships_ptr;

	void Draw(int col, int row, char newElement);

};

struct Ship {
	std::string name;	// Carrier (5), Battleship (4), Cruiser (3), Destroyer (2)
	int length;			// Length of the ship
	int xCoord;			// Starting x Coordinate
	int yCoord;			// Starting y Coordinate
	int horizontalDir;	// 1 = right, -1 = left, 0 = no change
	int verticalDir;	// 1 = down, -1 = up, 0 = no change
};


#endif