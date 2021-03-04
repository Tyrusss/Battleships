#include "Macros.h"
#include "Board.h"
#include "Game.h"

#include <iostream>
#include <tuple>

Game game(20);

Board* Player;
Board* Enemy;

int main() {

	Player = &(game.playerBoard);
	Enemy = &(game.aiBoard);

	Player->displayBoard();
	
	std::tuple<int, int> t;
	t = Player->placeShip(3);
	std::cout << std::get<0>(t) << ", " << std::get<1>(t);

	return 0;
}