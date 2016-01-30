#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H


typedef struct {
	char *board; // The board as an array of 0's and 1's.
	unsigned int cols; // The number of columns.
	unsigned int rows; // The number of rows.
} Game;
#endif
