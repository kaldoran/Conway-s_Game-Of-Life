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

void __gamePrint (Game* g, int (*pf)(const char *, ...)) {
	unsigned int x, y;

	if ( *pf == printw ) // If we use ncurses we need to replace cursor
		move(0, 0);
	
	(*pf)("Board size : \n");
	(*pf)("  %d Columns\n", g->cols);
	(*pf)("  %d rows\n", g->rows);

	__printLine(g, pf);

	for ( y = 0; y < g->rows; y++) {
		(*pf)("| ");
		for ( x = 0; x < g->cols; x++) {
			(*pf)("%c", ((g->current_board[POS(x, y, g)] == DEAD_CELL) ? '.' : '#'));	
		}
		
		(*pf)(" |\n");
	}
	
	__printLine(g, pf);
	
	if ( *pf == printw ) // If we use ncurses we need to refresh the display
		refresh();

	DEBUG_MSG("Print board finish\n");
}

void __swapGrid(Game* g) {
	char *tmp = g->current_board;
	g->current_board = g->next_board;
	g->next_board = tmp;
}

TickParam *newTickParam(int min, int max, Game* g) {
	TickParam *tp;

	if ( min > max ) {
		fprintf(stderr, "max need to greater than min\n");
		return NULL;
	}

	tp = NEW_ALLOC(TickParam);
	tp->min = min;
	tp->max = max;
	tp->g = g;

	return tp;	
}

void gamePrintInfo(Game* g, Option o) {
	#ifndef PRINT
	 	return;
	#endif

	int (*printFunc)(const char*, ...);	
	printFunc = ( o.use_ncurses ) ? &printw : &printf; 

	if ( o.max_tick >= 0 )
		printFunc("%d Generation left.\n", o.max_tick);
	
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
	
	g->current_board = __newBoard(rows, cols);
	g->next_board = __newBoard(rows, cols);

	return g;
}

void freeGame(Game* g)  {
	if ( g == NULL ) 
		return;

	free(g->current_board);
	free(g->next_board);
	free(g);
}

Game* generateRandomBoard(Option o) {

	unsigned int rows = 0, cols = 0;
	Game* g;
		
	g = __newGame(o.rows, o.cols);
	
	DEBUG_MSG("Ligne : %d, Cols : %d\n", rows, cols);
	for (rows = 0; rows < g->rows; rows++)
		for(cols = 0; cols < g->cols; cols++)
			g->current_board[POS(cols, rows, g)] = (
				( rand() % 100 >= POURCENT_BEEN_ALIVE ) ? 
					DEAD_CELL: 
					ALIVE_CELL
                );			
	DEBUG_MSG("Generate random finish");
	return g;
}

int __neightbourCell(unsigned int x, unsigned int y, Game *g) {
	unsigned int total = 0;
	char *b = g->current_board;

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
	else                                    return g->current_board[POS(x, y, g)];
}


void gameTick(TickParam* tp) {
	Game *g = tp->g;
	unsigned int x, y;
	
	for (y = 0; y < g->rows; y++)
		for(x = tp->min; x <= tp->max; x++)
			g->next_board[POS(x, y, g)] = __process(x, y, g);

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
		
		g->current_board[POS(cols, rows, g)] = reader;

		if ( reader == '\n' ) ++rows;
		if ( ++cols > g->cols ) cols = 0;
	}
	
	fclose(fp);

	if ( cols != g->cols && rows != g->rows ) { freeGame(g); return NULL; }
	return g;
}
