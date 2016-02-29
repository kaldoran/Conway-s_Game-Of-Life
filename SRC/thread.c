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

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "error.h"
#include "memory.h"
#include "thread.h"
#include "game.h"
#include "task.h"

ThreadInfo *newThreadInfo(unsigned int n, Game *g) {
    ThreadInfo *ti;

    ti = NEW_ALLOC(ThreadInfo);

    ti->g = g;
    ti->n = n;
    ti->total_end = 0;
    ti->should_end = false;
    ti->keep_task = false;
    ti->lock_work = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    ti->lock_end =  (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    ti->lock_end_cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    ti->task_pile = NEW_ALLOC(TaskPile);
    ti->plist =  NEW_ALLOC_K(n, pthread_t);

    if ( n > g->cols ) { /* If there is more thread than needed, then adjust the value */
        #ifdef PRINT
            fprintf(stderr, "[INFO] %d thread is/are useless\n", n - g->cols );
        #endif
        ti->n = g->cols; /* change default value */
    }

    return ti;
}

void freeThreadInfo(ThreadInfo *ti) {
    __freeTaskPile(ti->task_pile);
    pthread_mutex_destroy(&ti->lock_work);
    pthread_mutex_destroy(&ti->lock_end);
    pthread_cond_destroy(&ti->lock_end_cond);
    free(ti->plist);
    free(ti);
}

void createTask(ThreadInfo *ti, bool fine_grained) {
    unsigned int i;
    unsigned int j = 0;
    int slice_size = 0;
    Task *t = NULL;

    if ( ti->keep_task )
        return;

    pthread_mutex_lock(&ti->lock_work);
    
    slice_size = (!fine_grained ) ? ((int) ti->g->cols / ti->n) - 1 : 0; /* Calculate slice size */
    
    DEBUG_MSG("Slice Size : %d \n", slice_size + 1 );
    for ( i = 0; i < ti->g->cols; i = (t->max - t->min + 1) + i, ++j ) { /* J contains number of thread used */
        t = NEW_ALLOC(Task);
        
        t->min = i;                   /* The start of slice start at the last one done  */
        t->max = t->min + slice_size; /* And end at : The start + the slice size */
    
        if ( !fine_grained && j == ti->n - 1 ) /* If we are at the last thread available in average grained */
            t->max += ti->g->cols % ti->n;     /* Then give it the remaining column */

        if ( !fine_grained && t->max >= ti->g->cols ) t->max = ti->g->cols - 1; /* If we don't use the fine grained, then add missing column to */

        insertTask(ti->task_pile, t);
    }

    pthread_mutex_unlock(&ti->lock_work);

    /* set it to true when we've got some task and enought thread for never switch them */
    if ( (ti->g->cols == ti->n || !fine_grained) && !ti->keep_task ) 
        ti->keep_task = true;
}

/**
 * Private function which will lock the mutex, take a task and free the mutex
 * %param ti : ThreadInfo struct which contains all of the mutex / lock etc
 * %return   : A Task
 */
Task *__threadGetTask(ThreadInfo *ti) {
    Task *t = NULL;

    pthread_mutex_lock(&ti->lock_work);
    t = getTask(ti->task_pile);
    pthread_mutex_unlock(&ti->lock_work);
    
    return t;
}

/**
 * Private function which wait that all thread have finish there task
 * %param ti : ThreadInfo structu which contains all information relative to thread
 */
void __waitTickEnd(ThreadInfo* ti) {
    while (ti->total_end != ti->n) { usleep(5000); }    
}

void runThread(ThreadInfo* ti) {
    __waitTickEnd(ti); /* Wait that all have end there task before restart */
    pthread_mutex_lock(&ti->lock_end);

    ti->total_end = 0;
    pthread_cond_broadcast(&ti->lock_end_cond);
    pthread_mutex_unlock(&ti->lock_end);

    __waitTickEnd(ti); /* Wait all have finish before give hand to main */
}

/**
 * Private function that wait for all thread
 * %param ti : Thread info struct which contains all information relative to thread
 */
void __waitAllTick(ThreadInfo* ti) {
    pthread_mutex_lock(&ti->lock_end);
    ++ti->total_end;

    DEBUG_MSG("%d out of %d have finish, wait all others\n", ti->total_end, ti->n);
    pthread_cond_wait(&ti->lock_end_cond, &ti->lock_end);

    pthread_mutex_unlock(&ti->lock_end);
}

/**
 * Private function that process a thread action
 * When this function start, it wait for a broadcast to start
 * Then process is task and either wait or process a new task
 * %param ti : Thread info struct wich contains all information relative to thread
 */
void __processThread(ThreadInfo* ti) {
    Task *t = NULL;
    __waitAllTick(ti);

    while (!ti->should_end) {
    
        if ( t == NULL )
            t = __threadGetTask(ti);

        if ( t != NULL )
            gameTick(ti->g, t);
       
        if ( !ti->keep_task ) { 
            free(t); 
            t = NULL; 
        }
    
        if ( ti->keep_task || isEmpty(ti->task_pile) )
            __waitAllTick(ti);
    }

    pthread_mutex_lock(&ti->lock_end);
    ++ti->total_end;
    pthread_mutex_unlock(&ti->lock_end);
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
    runThread(ti);
    for ( i = 0; i < ti->n; i++) { 
        if ( pthread_join(ti->plist[i], NULL) ) 
            QUIT_MSG("Error while join thread %d\n", i);
    }

    DEBUG_MSG("All thread have finish they work\n");
}
