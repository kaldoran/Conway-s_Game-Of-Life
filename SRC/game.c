#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include "game.h"
#include "game_struct.h"
#include "memory.h"

int __position(int x, int y, Game* g) {
	return g->cols * y + x;
}

void __printLine(Game* g, int (*pf)(const char *, ...)) {
	int i = 0;
	(*pf)("+");
	for ( i = 0; i < g->cols + 2; i++ ) // the 2 '+' 
		(*pf)("-");
	(*pf)("+\n");
}

void gamePrint ( Game* g, int (*pf)(const char *, ...)) {
	int x, y;
	
	(*pf)("Board size : \n");
	(*pf)("  %d Columns\n", g->cols);
	(*pf)("  %d rows\n", g->rows);

	__printLine(g, pf);

	for ( y = 0; y < g->rows; y++) {
		(*pf)("| ");
		for ( x = 0; x < g->cols; x++) {
			(*pf)("%c", g->board[POS(x, y, g)]);	
		}
		
		(*pf)(" |\n");
	}
	
	__printLine(g, pf);
	
	#ifdef NCURSES
		refresh();
	#endif
}

char* __newBoard(int rows, int cols) {
	char* board = NEW_ALLOC_K(rows * cols, char);
	return board;
}

Game* __newGame(int rows, int cols) {
	Game* g = NEW_ALLOC(Game);
	
	g->rows = rows;
	g->cols = cols;
	
	g->board = __newBoard(rows, cols);
	
	return g;
}

void freeGame(Game* g)  {
	if ( g == NULL ) 
		return;

	if ( g->board != NULL ) 
		free(g->board);
	free(g);
}

Game* generateRandomBoard() {

	int rows = 0, cols = 0;
	Game* g;
		
	rows = rand() % ( MAX_ROWS_SIZE - MIN_ROWS_SIZE) + MIN_ROWS_SIZE;
	cols = rand() % ( MAX_COLS_SIZE - MIN_COLS_SIZE) + MIN_COLS_SIZE;	

	g = __newGame(rows, cols);
	
	fprintf(stderr, "Ligne : %d, Cols : %d\n", rows, cols);
	for (rows = 0; rows < g->rows; rows++)
		for(cols = 0; cols < g->cols; cols++)
			g->board[POS(cols, rows, g)] = (
				( rand() % 100 >= POURCENT_BEEN_ALIVE ) ? 
					DEAD_CELL: 
					ALIVE_CELL
                );			

	return g;
}


