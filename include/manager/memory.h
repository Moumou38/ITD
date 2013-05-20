#ifndef MEMORY_POOL
#define MEMORY_POOL

#include <stdlib.h>
#include <stdio.h>

typedef struct _allocatedMemory {
	void* data;
	size_t size;
	unsigned int refCount;
	struct _allocatedMemory* next;
} AllocatedMemory;

void* allocate(size_t size);

#endif
