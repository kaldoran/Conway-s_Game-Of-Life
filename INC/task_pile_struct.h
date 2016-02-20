#ifndef TASK_PILE_STRUCT
#define TASK_PILE_STRUCT

typedef struct Task {
    unsigned int min;
    unsigned int max;

    struct Task* next_task;
} Task;

typedef struct TaskPile {
  Task *first;
} TaskPile;


#endif
