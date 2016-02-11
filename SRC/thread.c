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

	TickParam **tpList = NULL;
	pthread_t *plist = NULL;

	tpList = NEW_ALLOC_K(n, tpList);
	plist = NEW_ALLOC_K(n, pthread_t);

	if ( n > g->cols ) { 
		fprintf(stderr, "[INFO] %d thread is/are useless\n", n - g->cols);
		n = g->cols;
	}

	slice_size = (!fine_grained) ? (int) g->cols / n : 1;

	DEBUG_MSG("Slice size : %d\n", slice_size);
	for ( i = 0; i < g->cols; ) {
		for ( j = 0; j < n; j++ ) {
			
			tpList[j] = NEW_ALLOC(TickParam);
		
			tpList[j]->g = g;
			tpList[j]->min = ( i + j ) * slice_size;
			tpList[j]->max = tpList[j]->min + (slice_size - 1);

			DEBUG_MSG("Thread %d process from %d to %d [%d cols]\n", j, tpList[j]->min, tpList[j]->max, tpList[j]->max - tpList[j]->min + 1);
				
			if ( !fine_grained && i == n - 1 ) tpList[j]->max += g->cols % n;
			
			if ( pthread_create(&plist[j], NULL, (void*) gameTick, tpList[j]) ) {
				fprintf(stderr, "Can't create thread %d\n", j);
				success = false;
			}
		}

		i += n * slice_size;
		success = __joinAllThread(n, plist);
		
		for ( j = 0; j < n; j++ ) free(tpList[j]);
		DEBUG_MSG("%d Value of i\n", i);
	}

	free(tpList);
	free(plist);

	return success;
}
