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

/*---------------------------------------------------------- */
/* AUTEUR : REYNAUD Nicolas                                  */
/* FICHIER : task_pile_struct.h                              */
/*                                                           */
/* - Debug Maccro [C99 Convention]                           */
/* - Quit maccro                                             */
/*---------------------------------------------------------- */


#ifndef TASK_PILE_STRUCT
#define TASK_PILE_STRUCT

/**
 * A task consist into a start column and an ending column
 */
typedef struct Task {
    unsigned int min;        /* Where the task need to start, i.e. column where start on board */
    unsigned int max;        /* Where the task need to end,   i.e column where stop on board   */

    struct Task* next_task;  /* Pointer to the next task */
} Task;

/**
 * A task pile is a stack of task, i.e FILO
 */
typedef struct TaskPile {
  Task *first;               /* Pointer on the first task of the task pile */
} TaskPile;


#endif
