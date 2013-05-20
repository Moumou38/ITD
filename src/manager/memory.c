#include "manager/memory.h"

unsigned long int allocated = 0;
AllocatedMemory* memoryList = NULL;
AllocatedMemory* memoryCurr = NULL;

void* allocatePtr(size_t size)
{
	void* tmp = malloc(size);
	if(tmp == NULL)
	{
		fprintf(stderr, "Unable to allocate memory.\n");
		exit(-1);
	}
	
	
	allocated += size + sizeof(AllocatedMemory);

	AllocatedMemory* mem = malloc(sizeof(AllocatedMemory));
	mem->data = tmp;
	mem->size = size;
	mem->refCount = 1;
	mem->next = NULL;

	if(memoryCurr == NULL) {
		memoryList = mem;
		memoryCurr = mem;
	} else {
		memoryCurr->next = mem;
		memoryCurr = mem;
	}
	fprintf(stderr, "Allocated %d bytes\n", size);

	return tmp;
}

void deallocatePtr(void* ptr)
{
	if(ptr == NULL)
		return;

	AllocatedMemory* tmp = memoryList, *last = NULL;
	while(tmp != NULL && tmp->data != ptr) 
	{
		last = tmp;		
		tmp = tmp->next;
	}

	if(tmp != NULL) 
	{
		allocated -= (tmp->size+sizeof(AllocatedMemory));
		if(last == NULL)
			memoryList = tmp->next;			
		else
			last = tmp->next;

		fprintf(stderr, "Freed %d bytes\n", tmp->size);
		free(tmp->data);
		free(tmp);
		
	}		
	if(memoryList == NULL)
		memoryCurr = NULL;
}

void* grabPtr(void* ptr)
{
	AllocatedMemory* tmp = memoryList;
	while(tmp != NULL && tmp->data != ptr) {
		tmp = tmp->next;
	}

	if(tmp != NULL)
		tmp->refCount++;
	
	return ptr;
}

void releasePtr(void* ptr)
{
	AllocatedMemory* tmp = memoryList;
	while(tmp != NULL && tmp->data != ptr) {
		tmp = tmp->next;
	}

	if(tmp != NULL)
	{
		tmp->refCount--;
		if(tmp->refCount <= 0)
			deallocatePtr(ptr);
	}
}

unsigned long int getAllocatedBytes()
{
	return allocated;
}

void freeMemoryList(AllocatedMemory* tmp)
{
	if(tmp == NULL)
		return;

	freeMemoryList(tmp);
	free(tmp->data);
	free(tmp);
}

void clearMemoryManager()
{
	freeMemoryList(memoryList);
	memoryList = NULL;
	memoryCurr = NULL;
	allocated = 0;
}
