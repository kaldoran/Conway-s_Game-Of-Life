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
/* FICHIER : task.h                                          */
/*---------------------------------------------------------- */

#ifndef TASK
#define TASK

#include "task_pile_struct.h"

/**
 * Function that create a new task
 * %param min : Column where the task will start
 * %param max : Column where the task will end
 * %return    : A new allocated task
 */
Task *newTask(int min, int max);

/**
 * Function which add a task to the pile
 * %param tpi : task pile where we need to add the task
 * %param t   : The task to add
 */
void insertTask(TaskPile *tpi, Task *t);

/**
 * Function which check if the pile is empty
 * %param tp : Task pile to check
 * %return   : true if the pile is empty
 *             false otherwise
 */
bool isEmpty(TaskPile* tp); 

/**
 * Function which get a task
 * %param tp : Task pile where we need to get a task
 * %return   : A task of the task pile
 */
Task *getTask(TaskPile* tp);

/**
 * Private function that shouldn't be used [only use in thread.c]
 * The definition of this function is in task.c [all information are there]
 */
void __freeTaskPile(TaskPile* tp);

#endif 
