#include "Macros.h"
#include "Board.h"
#include "Game.h"

#include <iostream>
#include <tuple>

Game game(15);

Board* Player;
//EnemyBoard* Enemy;

int main() {
	srand(time(NULL)); // initialise RNG seed

	Player = &(game.playerBoard);
	//Enemy = &(game.aiBoard);

	Player->placeShips();

	return 0;
}