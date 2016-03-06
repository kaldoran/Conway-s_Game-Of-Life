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
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>

#include "error.h"
#include "game.h"
#include "task.h"
#include "ncurses.h"
#include "option.h"
#include "thread.h"

int main(int argc, char* argv[]) {

    srand(time(NULL));

    clock_t time;

    Option o;
    Game* g = NULL; 
    Task *t = NULL;
    ThreadInfo *ti = NULL;

    o = getOption(argc, argv);  /* Get all option     */

    if ( *o.file_path != '\0' ) /* If path file is not empty */
        if ( (g = loadBoard(o.file_path)) == NULL ) /* then use the given file [load id] */
            fprintf(stderr, "Can't load file %s\n", o.file_path);

    if ( g == NULL ) /* If load of file fail Or no grid given */
        g = generateRandomBoard(o); /* then create one */

    if ( o.use_ncurses ) /* If we use ncurses */
        initNCurses();   /* Then we init the display */

    if ( o.nb_thread == 0 ) { /* If there is no threa given, then we use sequential version */
        t = newTask(0, g->cols - 1); /* And said to the main thread to threat all columns */
    } else {
        ti = newThreadInfo(o.nb_thread, g);
        createNThread(ti);
    }

    time = clock();
    while(o.max_tick != 0) {         /* Inifinit loop if total tick not given */

        gamePrintInfo(g, o);         
        
        if ( o.nb_thread == 0 ) {    /* if there is 0 thread then do not use thread method  */
            gameTick(g, t);            /* Lets the game tick */
        } else {
            createTask(ti, o.use_fine_grained);
            runThread(ti);
        }
        
        __swapGrid(g);
        --o.max_tick;
        
        #ifdef PRINT                 /* If we print we add some delay without it we can't see the grid */
            usleep(400000);
        #endif
    }
    
    time = clock() - time;
    printf("Time : %f\n", (double)(time) / CLOCKS_PER_SEC);
    
    if ( o.use_ncurses) /* If we use ncurses ( and then init it ) */
        endNCurses();   /* we need to clear display info */

    if ( o.save_file )     
        saveBoard(g);

    if ( o.nb_thread == 0 ) {
        free(t);
    } else {
        endNThread(ti);
        freeThreadInfo(ti);
    }

    freeGame(g);           /* Free space we are not in Java */
    
    exit(EXIT_SUCCESS);
}

