#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

#define NEW_ALLOC(OBJECT) (NEW_ALLOC_K(1, OBJECT))

#define NEW_ALLOC_K(K, OBJECT) (__memAlloc(K, sizeof(OBJECT)))

void *__memAlloc(int total, size_t object_size);

#endif
