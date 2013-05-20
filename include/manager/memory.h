#ifndef MEMORY_MANAGER
#define MEMORY_MANAGER

#include <stdlib.h>
#include <stdio.h>

typedef struct _allocatedMemory {
	void* data;
	size_t size;
	unsigned int refCount;
	struct _allocatedMemory* next;
} AllocatedMemory;

void* allocatePtr(size_t size);

void deallocatePtr(void* ptr);

void* grabPtr(void* ptr);

void releasePtr(void* ptr);

unsigned long int getAllocatedBytes();

void clearMemoryManager();

#endif
