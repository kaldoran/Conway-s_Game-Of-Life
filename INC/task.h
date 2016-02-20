#ifndef TASK
#define TASK

#include "task_pile_struct.h"

Task *newTask(int min, int max);

void insertTask(TaskPile *tpi, Task *t);

bool isEmpty(TaskPile* tp); 

Task *getTask(TaskPile* tp);

void __freeTaskPile(TaskPile* tp);

#endif 
