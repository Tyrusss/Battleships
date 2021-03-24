#include "Macros.h"
#include "Board.h"
#include "Game.h"

#include <iostream>
#include <tuple>

Game game(15);

Board* Player;
Board* Enemy;

int main() {
	Player = &(game.playerBoard);
	Enemy = &(game.aiBoard);

	Player->placeShips();

	return 0;
}