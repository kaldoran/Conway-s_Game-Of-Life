#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include "error.h"
#include "game.h"
#include "game_struct.h"
#include "memory.h"

int __position(unsigned int x, unsigned int y, Game* g) {
	return g->cols * y + x;
}

void __printLine(Game* g, int (*pf)(const char *, ...)) {
	unsigned int i = 0;
	(*pf)("+");
	for ( i = 0; i < g->cols + 2; i++ ) // the 2 '+' 
		(*pf)("-");
	(*pf)("+\n");
}

void __gamePrint ( Game* g, int (*pf)(const char *, ...)) {
	unsigned int x, y;

	#ifdef NCURSES
		move(0, 0);
	#endif

	(*pf)("Board size : \n");
	(*pf)("  %d Columns\n", g->cols);
	(*pf)("  %d rows\n", g->rows);

	__printLine(g, pf);

	for ( y = 0; y < g->rows; y++) {
		(*pf)("| ");
		for ( x = 0; x < g->cols; x++) {
			(*pf)("%c", ((g->board[POS(x, y, g)] == DEAD_CELL) ? '.' : '#'));	
		}
		
		(*pf)(" |\n");
	}
	
	__printLine(g, pf);
	
	#ifdef NCURSES
		refresh();
	#endif

	DEBUG_MSG("Print board finish\n");
}

void gamePrintInfo(Game* g, int max_tick) {
	#ifndef PRINT
	 	return;
	#endif

	int (*printFunc)(const char*, ...);	
	printFunc = 
		#ifdef NCURSES 
			&printw;
		#else 
			&printf; 
		#endif

	printFunc("%d Generation left.\n", max_tick);
	__gamePrint(g, printFunc);
}

char* __newBoard(unsigned int rows, unsigned int cols) {
	char* board = NEW_ALLOC_K(rows * cols, char);
	return board;
}

Game* __newGame(unsigned int rows, unsigned int cols) {
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

	unsigned int rows = 0, cols = 0;
	Game* g;
		
	rows = rand() % ( MAX_ROWS_SIZE - MIN_ROWS_SIZE) + MIN_ROWS_SIZE;
	cols = rand() % ( MAX_COLS_SIZE - MIN_COLS_SIZE) + MIN_COLS_SIZE;	

	g = __newGame(rows, cols);
	
	DEBUG_MSG("Ligne : %d, Cols : %d\n", rows, cols);
	for (rows = 0; rows < g->rows; rows++)
		for(cols = 0; cols < g->cols; cols++)
			g->board[POS(cols, rows, g)] = (
				( rand() % 100 >= POURCENT_BEEN_ALIVE ) ? 
					DEAD_CELL: 
					ALIVE_CELL
                );			
	DEBUG_MSG("Generate random finish");
	return g;
}

int __neightbourCell(unsigned int x, unsigned int y, Game *g) {
	unsigned int total = 0;
	char *b = g->board;

	if ( x % g->cols != g->cols - 1) {
		total += b[POS(x + 1, y,     g)]; // Right
		if ( y < g->rows - 1 ) total += b[POS(x + 1, y + 1, g)]; // Right - Down
		if ( y > 0 )           total += b[POS(x + 1, y - 1, g)]; // Up - Right
	}

	if ( x % g->cols != 0 ) { 
		total += b[POS(x - 1, y    , g)]; // Left
		if ( y < g->rows - 1 ) total += b[POS(x - 1, y + 1, g)]; // Left - Down
		if ( y > 0 )           total += b[POS(x - 1, y - 1, g)]; // Up - Left
	}

	if ( y < g->rows - 1 ) total += b[POS(x    , y + 1, g)]; // Down
	if ( y > 0 )           total += b[POS(x    , y - 1, g)]; // Up 

	return total;
}

char __process(unsigned int x, unsigned int y, Game* g) {
	unsigned int neightbour = __neightbourCell(x, y, g);	

	if ( neightbour < 2 || neightbour > 3 ) return DEAD_CELL;
	else if ( neightbour == 3 )             return ALIVE_CELL;
	else                                    return g->board[POS(x, y, g)];
}

void gameTick(Game* g) {
	unsigned int x, y;
	char* new_board;
	
	new_board = __newBoard(g->rows, g->cols);
	
	for (y = 0; y < g->rows; y++)
		for(x = 0; x < g->cols; x++)
			new_board[POS(x, y, g)] = __process(x, y, g);

	free(g->board);
	g->board = new_board;

	DEBUG_MSG("Game tick finish");
}


Game* loadBoard(char* name) { 
	char reader = ' ';
	unsigned int rows = 0, cols = 0;
	FILE* fp = NULL;	
	Game *g = NULL;	

	if ( (fp = fopen(name, "r")) == NULL ) return NULL;
	if ( fscanf(fp, "Rows : %d\nCols : %d\n", &rows, &cols) != 2) { fclose(fp); return NULL; }

	g = __newGame(rows, cols);

	DEBUG_MSG("Ligne : %d, Cols : %d\n", rows, cols);
	rows = 0; cols = 0; // Reinit variable
	
	while ( (reader = fgetc(fp)) != EOF ) {
		if ( reader == '.' ) reader = DEAD_CELL;
		if ( reader == '#' ) reader = ALIVE_CELL;
		
		g->board[POS(cols, rows, g)] = reader;

		if ( reader == '\n' ) ++rows;
		if ( ++cols > g->cols ) cols = 0;
	}
	
	fclose(fp);

	if ( cols != g->cols && rows != g->rows ) { freeGame(g); return NULL; }
	return g;
}
