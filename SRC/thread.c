#include <stdio.h>
#include <pthread.h>

#include "memory.h"
#include "thread.h"
#include "game.h"
#include "tick_param_struct.h"

void a(void *p) {

	TickParam *tp = (TickParam*) p;

	while(1) {
		gameTick(tp);
		fprintf(stderr, "Salut - %p\n", (TickParam*) (tp->g));

	}
}

pthread_t *creatNThread(int n, Game *g) {
	int i = 0;
	pthread_t *plist = NULL;

	plist = NEW_ALLOC_K(n, pthread_t);

	for ( i = 0; i < n; i++) {

		TickParam *tp = NEW_ALLOC(TickParam);
		tp->g = g;
		pthread_attr_t* attrs = NEW_ALLOC(pthread_attr_t);
		pthread_attr_init(attrs);
		pthread_t *p = NEW_ALLOC(pthread_t);
		pthread_create(p, attrs, (void*) a, tp);
		printf("Allocate Thread");
	}

	return plist;
}
