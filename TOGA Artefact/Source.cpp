#include "Macros.h"
#include "Board.h"
#include "Game.h"

#include <iostream>

Game game(10);

Board* Player;
Board* Enemy;

int main() {

	Player = &(game.playerBoard);
	Enemy = &(game.aiBoard);

	Player->displayBoard();
	//Enemy->displayBoard();
	Player->placeShip(1);
	Player->displayBoard();

	return 0;
}