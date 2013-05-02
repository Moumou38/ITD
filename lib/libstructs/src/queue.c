#include "../include/queue.h"

Queue* queue_init() 
{
	Queue* q = malloc(sizeof(Queue));
	if(q == NULL)
		return NULL;

	q->data = NULL;
	q->last = NULL;
	q->size = 0;
	return q;
}

int queue_push(Queue* file, void* value)
{
	Data* tmp, *last = NULL;
	if(file == NULL || value == NULL) {
		return -1;
	}

	tmp = malloc(sizeof(Data));
	if(tmp == NULL)
		return -1;

	tmp->value = value;
	tmp->next = NULL;
		
	if(file->last == NULL) {
		file->data = tmp;
		file->last = tmp;
	}
	else {
		file->last->next = tmp;
		file->last = tmp;
	}

	file->size++;
	/*	return 1;
	}
	else {
		return -1;
	}*/
}

int queue_pop(Queue* file)
{
	Data* tmp, *next;
	if(file == NULL || file->data == NULL)
		return -1;
	tmp = file->data;
	
	file->data = tmp->next;
	if(file->last == tmp)
		file->last = NULL;
	free(tmp);
	file->size--;
	return 1;
}

void* queue_peek(Queue* file)
{
	if(file == NULL || file->data == NULL)
		return NULL;

	return file->data->value;
}

void queue_print(Queue* file)
{
	Data *tmp;
	if(file == NULL)
	{
		printf("La file est NULL\n");
		return;
	}

	printf("Nombre d'éléments: %d\n", file->size);
	tmp = file->data;
	while(tmp != NULL) {
		printf("%d %d %d\n", (int)tmp, (int)tmp->value, (int)tmp->next);
		tmp = tmp->next;
	}
}

int queue_size(Queue* file)
{
	if(file == NULL)
		return -1;

	else
		return file->size;
}

void queue_delete(Queue* file)
{
	if(file == NULL)
		return;

	freeData(file->data);
	free(file);
	file = NULL;
}

