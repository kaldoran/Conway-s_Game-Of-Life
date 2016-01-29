#include "error.h"
#include "memory.h"

void *__memAlloc(int total, size_t object_size) {

	void *p = calloc(total, object_size);

	if ( p == NULL ) 
		QUIT_MSG("Canno't allocate new object\n");

	return p;

}
