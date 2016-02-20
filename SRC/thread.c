#include <stdio.h>
#include <pthread.h>

#include "error.h"
#include "memory.h"
#include "thread.h"
#include "game.h"
#include "task.h"

ThreadInfo *newThreadInfo(unsigned int n, Game *g, bool fine_grained) {
    ThreadInfo *ti;

    ti = NEW_ALLOC(ThreadInfo);

	if ( n > g->cols ) { /* If there is more thread than needed, then adjust the value */
		fprintf(stderr, "[INFO] %d thread is/are useless\n", n - g->cols);
		ti->n = g->cols;
	}

    ti->g = g;
    ti->total_end = 0;
    ti->should_end = false;
    ti->keep_task = (g->cols == n || !fine_grained);
    ti->lock_work = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    ti->lock_end =  (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    ti->lock_end_cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    ti->task_pile= NEW_ALLOC(ti->task_pile);
    ti->plist =  NEW_ALLOC_K(n, pthread_t);
    
    return ti;
}

void freeThreadInfo(ThreadInfo *ti) {
    __freeTaskPile(ti->task_pile);
    free(ti->plist);
    free(ti);
}

void createTask(ThreadInfo *ti, bool fine_grained) {
    unsigned int i;
    int slice_size = 0;
    Task *t = NULL;

    if ( ti->keep_task ) 
        return;

    pthread_mutex_lock(&ti->lock_work);

	slice_size = (!fine_grained) ? (int) ti->g->cols / ti->n : 1; /* Calculate slice size */
    
    for ( i = 0; i < ti->g->cols; i++ ) {
	    t = NEW_ALLOC(t); /* Create new task */
		
	    t->min = i * slice_size;            /* The start of slice start at the last one done  */
	    t->max = t->min + (slice_size - 1); /* And end at : The start + the slice size */

        DEBUG_MSG("Thread %d process from %d to %d [%d cols]\n", i, t->min, t->max, t->max - t->min + 1);
				
	    if ( !fine_grained && i == ti->g->cols - 1 ) t->max += ti->g->cols % ti->n; /* If we don't use the fine grained, then add missing column to */
    
        insertTask(ti->task_pile, t);
    }

    pthread_mutex_unlock(&ti->lock_work);
}


Task *__threadGetTask(ThreadInfo *ti) {
    Task *t = NULL;

    pthread_mutex_lock(&ti->lock_work);
    t = getTask(ti->task_pile);
    pthread_mutex_unlock(&ti->lock_work);
    
    return t;
}

void runThread(ThreadInfo* ti) {
    pthread_mutex_lock(&ti->lock_end);
    
    ti->total_end = 0;
    pthread_cond_broadcast(&ti->lock_end_cond);
    pthread_mutex_unlock(&ti->lock_end);
}

void __waitAllTick(ThreadInfo* ti) {
    pthread_mutex_lock(&ti->lock_end);

    ++ti->total_end;
    pthread_cond_wait(&ti->lock_end_cond, &ti->lock_end);

    pthread_mutex_unlock(&ti->lock_end);
}

void __processThread(ThreadInfo* ti) {
    Task *t = NULL;
    __waitAllTick(ti);

    while (!ti->should_end) {
        
        if ( t == NULL )
            t = __threadGetTask(ti);

        gameTick(ti->g, t);

        if ( ti->keep_task || isEmpty(ti->task_pile) )
            __waitAllTick(ti);
        else 
            free(t);
    }
}

void createNThread(ThreadInfo *ti) {
    unsigned int i = 0;

    for ( i = 0; i < ti->n; i++) 
		if ( pthread_create(&ti->plist[i], NULL, (void*) __processThread, ti) ) /* Create the thread here */
            QUIT_MSG("Can't create thread %d\n", i);
}

void endNThread(ThreadInfo *ti) {
    unsigned int i;
    ti->should_end = true;

    for ( i = 0; i < ti->n; i++) { 
        pthread_exit((void *) "Bye bye"); 

        if ( pthread_join(ti->plist[i], NULL) ) 
            QUIT_MSG("Error while join thread %d\n", i);
    }
}
