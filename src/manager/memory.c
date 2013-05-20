#include "manager/memory.h"

unsigned long int allocated = 0;
AllocatedMemory* memoryList = NULL;
AllocatedMemory* memoryCurr = NULL;

void* allocate(size_t size)
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

	return tmp;
}

void deallocate(void* ptr)
{
	if(ptr == NULL)
		return;

	AllocatedMemory* tmp = memoryList, *last = NULL;
	while(tmp != NULL) {
		if(tmp->data != ptr) {
			last = tmp;		
			tmp = tmp->next;
		}
		else {
			allocated -= (tmp->size+sizeof(AllocatedMemory));
			if(last == NULL)
				memoryList = tmp->next;			
			else
				last = tmp->next;

			free(tmp->data);
			free(tmp);
		}
	}
	if(memoryList == NULL)
		memoryCurr = NULL;
}
