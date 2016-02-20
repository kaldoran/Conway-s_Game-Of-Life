/*
 *  Copyright (C) 2016-2016 REYNAUD Nicolas
 *  Author : REYNAUD Nicolas <kaldoran [at] live.fr>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 */

#ifndef GAME_H
#define GAME_H

#include "game_struct.h"
#include "option_struct.h"

#include "task_pile_struct.h"

#define MIN_COLS_SIZE 5
#define MIN_ROWS_SIZE 3

#define MAX_COLS_SIZE 50
#define MAX_ROWS_SIZE 30
#define POURCENT_BEEN_ALIVE 15

#define DEAD_CELL 0
#define ALIVE_CELL 1

#define POS(X, Y, G) (__position(X,Y,G))

void gamePrintInfo ( Game* g, Option o);

void freeGame(Game* g);

Game* generateRandomBoard(Option o);

void gameTick(Game *g, Task *t);

void __swapGrid(Game* g);

Game* loadBoard(char* name);

bool saveBoard(Game *g);
#endif
