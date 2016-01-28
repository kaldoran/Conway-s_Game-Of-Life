#include <stdlib.h>

#include "game_struct.h"
#include "game.h"


#define POS(X, Y, G) (__position(X,Y,G))

int __position(int x, int y, Game* g) {
	return g->cols * y + x;
}

void gamePrint ( Game* g, int (*pf)(const char *, ...)) {
	int i, j;

	for ( i = 0; i <= g->rows; i++) {
		for ( j = 0; j <= g->cols; j++) {
			(*pf)("%c", g->board[POS(i, j, g)]);	
		}

		(*pf)("\n");
	}
}

Game* generateRandomBoard() {
	

}
