#include <stdio.h>
#include <pthread.h>

#include "error.h"
#include "memory.h"
#include "thread.h"
#include "game.h"
#include "tick_param_struct.h"

bool __joinAllThread(int n, pthread_t *plist) {
	int i;
	bool success = true;

	for ( i = 0; i < n; i++ ) {
		if ( pthread_join(plist[i], NULL) ) {
			fprintf(stderr, "Error on join thread %d\n", i);
			success = false;
		}
	}

	DEBUG_MSG("All joined thread finished\n");

	return success;
}

bool createNThreadF(unsigned int n, Game *g, bool fine_grained) {
	bool success = true;
	unsigned int slice_size;
	unsigned int j;
	unsigned int i;

	TickParam **tpList = NULL; // Will contains list of all rang to do
	pthread_t *plist = NULL;   // Will contains the list of thread

	tpList = NEW_ALLOC_K(n, tpList); // Allocate the 2 Array
	plist = NEW_ALLOC_K(n, pthread_t);

	if ( n > g->cols ) { // If there is more thread than needed, then adjust the value
		fprintf(stderr, "[INFO] %d thread is/are useless\n", n - g->cols);
		n = g->cols;
	}

	slice_size = (!fine_grained) ? (int) g->cols / n : 1; // If we use a fine_grained then all slice equal to 1

	for ( i = 0; i < g->cols; ) {   // This loop is useless ( and will be pass after one iteration if we dont use fine grained) 
		for ( j = 0; j < n; j++ ) { // This loop create the n thread and give each of them a slice to treat
			
			tpList[j] = NEW_ALLOC(TickParam); // Allocate the struct that give the slice rang to treat
		
			tpList[j]->g = g;                 // Copy the pointer cause we need the game board
			tpList[j]->min = ( i + j ) * slice_size; // The start of slice start at the last one done 
			tpList[j]->max = tpList[j]->min + (slice_size - 1); // And end at : The start + the slice size

			DEBUG_MSG("Thread %d process from %d to %d [%d cols]\n", j, tpList[j]->min, tpList[j]->max, tpList[j]->max - tpList[j]->min + 1);
				
			if ( !fine_grained && i == n - 1 ) tpList[j]->max += g->cols % n; // If we don't use the fine grained, then add missing column to
			                                                                  // the last thread
			
			if ( pthread_create(&plist[j], NULL, (void*) gameTick, tpList[j]) ) { // Create the thread here
				fprintf(stderr, "Can't create thread %d\n", j);
				success = false;
			}
		}

		success = __joinAllThread(n, plist); // Join all thread
		
		for ( j = 0; j < n; j++ ) free(tpList[j]); // Free all allocated struct (avoid memory leak )
		i += n * slice_size; 
	}

	free(tpList); // Avoid memory leak, free all memory used
	free(plist);

	return success;
}
