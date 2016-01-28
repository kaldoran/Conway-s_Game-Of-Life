#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H


typedef struct {
	char *board; // The board as an array of 0's and 1's.
	int cols; // The number of columns.
	int rows; // The number of rows.
} Game;
#endif
