#ifndef GAME_H
#define GAME_H

#include "game_struct.h"

#define MIN_COLS_SIZE 5
#define MIN_ROWS_SIZE 3

#define MAX_COLS_SIZE 50
#define MAX_ROWS_SIZE 30
#define POURCENT_BEEN_ALIVE 15


#define DEAD_CELL '.'
#define ALIVE_CELL '#'


#define POS(X, Y, G) (__position(X,Y,G))

void gamePrint ( Game* g, int (*pf)(const char *, ...));
// void gamePrint ( Game* g, void (*printingFunction)(char *) );

void freeGame(Game* g);

Game* generateRandomBoard();

#endif
