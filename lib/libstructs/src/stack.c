#include "../include/stack.h"

Stack* stack_init() 
{
	Stack* s = malloc(sizeof(Stack));
	if(s == NULL)
		return NULL;
	
	s->first = NULL;;
	s->size = 0;
	return s;
}

int stack_push(Stack* pile, void* value)
{
	Data* tmp;
	if(pile == NULL || value == NULL) {
		return -1;
	}

	tmp = malloc(sizeof(Data));
	if(tmp == NULL)
			return -1;

	tmp->value = value;
	tmp->prev = NULL;
	tmp->next = pile->first;
	
	pile->first = tmp;

	pile->size++;
	return 1;
}

int stack_pop(Stack* pile)
{
	Data *tmp, *last;
	if(pile == NULL || pile->first == NULL)
		return -1;

	tmp = pile->first;
	pile->first = tmp->next;

	free(tmp);
	pile->size--;
	
	return 1;
}

void* stack_peek(Stack* pile)
{
	if(pile == NULL || pile->first == NULL)
		return NULL;

	return pile->first->value;
}

void stack_print(Stack* pile)
{
	Data *tmp;
	if(pile == NULL)
	{
		printf("La pile est NULL\n");
		return;
	}

	printf("Nombre d'éléments: %d\n", pile->size);
	tmp = pile->first;
	while(tmp != NULL) {
		printf("%d %d %d\n", (int)tmp, (int)tmp->value, (int)tmp->next);
		tmp = tmp->next;
	}
}

int stack_size(Stack* pile)
{
	if(pile == NULL)
		return -1;

	else
		return pile->size;
}

void stack_delete(Stack* stack)
{
	if(stack == NULL)
		return;

	freeData(stack->first);
	free(stack);
	stack = NULL;
}
