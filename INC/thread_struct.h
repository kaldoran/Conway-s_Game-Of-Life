#ifndef THREAD_STRUCT
#define THREAD_STRUCT

#include <stdbool.h>
#include <pthread.h>

#include "task_pile_struct.h"

typedef struct ThreadInfo {
    bool keep_task;
    bool should_end;
    unsigned int n; /* Total Number of thread */
    
    Game *g;        /* Contains a copy of the pointer of Game [Game is in main thread] */
    pthread_mutex_t lock_work; /* Lock wait take / place job into the job list */
    
    int total_end;
    pthread_mutex_t lock_end;
    pthread_cond_t  lock_end_cond;

    TaskPile *task_pile; /* list of all task (could be empty is keep_task is set */
    pthread_t *plist;
} ThreadInfo;

#endif
