#include <stdio.h>
#include <pthread.h>

#include "memory.h"
#include "thread.h"

void a() {
	fprintf(stderr, "Salut\n");
}

pthread_t *creatNThread(int n) {
	int i = 0;
	pthread_t *plist = NULL;

	plist = NEW_ALLOC_K(n, pthread_t);

	for ( i = 0; i < n; i++) {
		pthread_attr_t* attrs = NEW_ALLOC(pthread_attr_t);
		pthread_attr_init(attrs);
		pthread_t *p = NEW_ALLOC(pthread_t);
		pthread_create(p, attrs, (void*) a, NULL);
		printf("Allocate Thread");
	}

	return plist;
}
