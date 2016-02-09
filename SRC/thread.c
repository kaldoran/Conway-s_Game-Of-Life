#include <stdio.h>
#include <pthread.h>

#include "memory.h"
#include "thread.h"
#include "game.h"
void a(void *p) {
	threadParam *tp = (threadParam*) p;

	fprintf(stderr, "Salut - %p\n", (threadParam*) (tp->g));
}

pthread_t *creatNThread(int n, Game *g) {
	int i = 0;
	pthread_t *plist = NULL;

	plist = NEW_ALLOC_K(n, pthread_t);

	for ( i = 0; i < n; i++) {

		threadParam *tp = NEW_ALLOC(threadParam);
		tp->g = g;
		pthread_attr_t* attrs = NEW_ALLOC(pthread_attr_t);
		pthread_attr_init(attrs);
		pthread_t *p = NEW_ALLOC(pthread_t);
		pthread_create(p, attrs, (void*) a, tp);
		printf("Allocate Thread");
	}

	return plist;
}
