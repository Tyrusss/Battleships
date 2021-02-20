#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include <string>

class Board {

public:
	std::string owner;

	void initBoard();
	void displayBoard();
	void placeShip(int shipSize);

	Board(int size);

private:
	int board_size;
	std::vector<std::vector<char>> grid;

	void Draw(int col, int row, char newElement);

};

#endif