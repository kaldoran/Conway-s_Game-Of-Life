#include <stdbool.h>

#include "error.h"
#include "task.h"
#include "memory.h"

Task *newTask(int min, int max) {
	Task *t;

	if ( min > max )
		QUIT_MSG("max need to greater than min\n");

	t = NEW_ALLOC(t);
	t->min = min;
	t->max = max;
    t->next_task = NULL;

    return t;	
}

void insertTask(TaskPile *tp, Task *t) {

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

    return t;
}

void __freeTaskPile(TaskPile *tp) {
    while (!isEmpty(tp))
        free(getTask(tp));

    free(tp);
}
