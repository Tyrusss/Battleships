#ifndef _GAME_H
#define _GAME_H

#include "Board.h"

class Game {
public:
	int size;
	Board playerBoard;
	//EnemyBoard aiBoard;

	Game(int boardSize);

};

#endif