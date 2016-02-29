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
/* FICHIER : thread.h                                        */
/*                                                           */
/* - Debug Maccro [C99 Convention]                           */
/* - Quit maccro                                             */
/*---------------------------------------------------------- */


#ifndef THREAD
#define THREAD

#include <stdbool.h>

#include "game_struct.h"
#include "thread_struct.h"

/**
 * Function that create new thread information, this function also set the real number of usefull thread
 * %param n : Total number of thread that need to be create
 * %param g : Game struct which contains all information relative to the game where thread going to iterate
 * %return  : Thread information containing all revelent information
 */
ThreadInfo *newThreadInfo(unsigned int n, Game *g);

/**
 * Function which free the thread info
 * %param ti : Thread info to free
 */
void freeThreadInfo(ThreadInfo *ti);

/**
 * Function which create a new task
 * %param ti : thread information which contains lock and all revelent information about thread
 * %param fine_grained : Bool which say if we use the fine grained method or not
 */
void createTask(ThreadInfo *ti, bool fine_grained);

/**
 * Function that make the thread run [.ie broadcast a start message ]
 * %param ti : Thread information which contains all revelent information about thread [ Mutex etc ]
 */
void runThread(ThreadInfo *ti); 

/**
 * Function that create N thread, according to the thread info struct
 * %param ti : thread information structure which contains information about the thread
 *             [ total number of thread / mutex etc ]
 */
void createNThread(ThreadInfo *ti);

/**
 * Function which stop all thread, this function make them run after said that they need to stop
 * then it wait for all thread
 * %param ti : Thread information struct which contains the list of thread
 */
void endNThread(ThreadInfo *ti); 

#endif
