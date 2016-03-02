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

#include <stdbool.h>

#include "error.h"
#include "task.h"
#include "memory.h"

Task *newTask(int min, int max) {
    Task *t;

    if ( min > max )
        QUIT_MSG("max need to greater than min\n");

    t = NEW_ALLOC(Task);
    t->min = min;
    t->max = max;
    t->next_task = NULL;

    return t;    
}

void insertTask(TaskPile *tp, Task *t) {
    DEBUG_MSG("We add task from : %d to %d |Taks : %p - Next : %p|\n", t->min, t->max, t, t->next_task);

    if ( tp->first != NULL ) 
        t->next_task = tp->first;

    tp->first = t;
}

bool isEmpty(TaskPile *tp) {
    return tp->first == NULL;
}

Task *getTask(TaskPile *tp) {
    Task *t = NULL;
    if ( isEmpty(tp) )
        return NULL;

    t = tp->first;
    tp->first = t->next_task;

    DEBUG_MSG("Get : %p | tp->first : %p\n", t, tp->first);
    return t;
}

/**
 * Private function that free the task pile and all remaining task if there is some
 * %param tp : Pointer of the pile which we need to free
 */
void __freeTaskPile(TaskPile *tp) {
    while (!isEmpty(tp))
        free(getTask(tp));

    free(tp);
}
