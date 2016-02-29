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
/* FICHIER : error.h                                         */
/*                                                           */
/* - Debug Maccro [C99 Convention]                           */
/* - Quit maccro                                             */
/*---------------------------------------------------------- */


#ifndef OPTION_STRUCT
#define OPTION_STRUCT

#include <stdbool.h>

/** 
 * Structure that will contains all of the option 
 */
typedef struct Option {
    int max_tick;             /* How much tick we need to do            - Default : 100 */
    char* file_path;          /* Path to the file to load               - Default : "" */
    unsigned int nb_thread;   /* Total number of thread to use          - Default : 0  */
    unsigned int rows;        /* Number of rows to generate             - Default : Random */
    unsigned int cols;        /* Number of columns to generate          - Default : Random */
    bool use_ncurses;         /* Do we use ncurses for the display ?    - Default : false */
    bool use_fine_grained;    /* Do we use fine grain in multi thread ? - Default : false */
    bool save_file;           /* Do we need to save the last grid ?     - Default : false */
} Option;

#endif
