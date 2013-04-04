#include "../include/doublelinkedlist.h"

DoubleLinkedList* dll_init() 
{
	DoubleLinkedList* l = malloc(sizeof(DoubleLinkedList));

	if(l == NULL)
		return NULL;

	l->begin = NULL;
	l->end = NULL;
	l->size = 0;
	return l;
}

int dll_add(DoubleLinkedList* list, void* value, unsigned int pos)
{
	Data *tmp = NULL, *last = NULL, *add = NULL;
	unsigned int curr = 0;
	//printf("adding %d at %d\n", (int)value, pos);
	if(list == NULL || value == NULL) {
		return -1;
	}


	// Création du nouveau maillon
	add = malloc(sizeof(Data));
	if(add == NULL)
		return -1;
	add->value = value;
	add->next = NULL;
	add->prev = NULL;
	
	if(list->begin == NULL) {
		list->begin = add;
		list->end = add;
	}
	else {
		// Recherche et ajout du maillon en bonne position.
		if(pos == 0) {
			if(list->begin != NULL)
				list->begin->prev = add;

			add->next = list->begin;
			list->begin = add;
		}
		else if(pos >= list->size) {
			if(list->end != NULL)
				list->end->next = add;

			add->prev = list->end;
			list->end = add;
		}
		else {
			last = dll_getData(list, pos-1);
			tmp = last->next;
			tmp->prev = add;
			last->next = add;
			add->next = tmp;
			add->prev = last;
		}
	}
	//printf("added: %d %d %d %d %d\n", pos, (int)add, (int)add->value, (int)add->prev, (int)add->next);
	list->size++;
	return 1;
}

int dll_append(DoubleLinkedList* list, void* value)
{
	if(list == NULL)
		return -1;

	return dll_add(list, value, list->size);
}

int dll_prepend(DoubleLinkedList* list, void* value)
{
	if(list == NULL)
		return -1;

	return dll_add(list, value, 0);
}

int dll_remove(DoubleLinkedList* list, unsigned int pos)
{
	Data *tmp, *last;
	unsigned int curr = 0;
	//printf("removing at %d\n", pos);
	if(list == NULL || list->size <= pos)
		return -1;

	
	if(pos == 0)
	{
		tmp = list->begin;
		list->begin = tmp->next;
		if(list->begin != NULL)
			list->begin->prev = NULL;
	}
	else if(pos == (list->size-1))
	{
		//printf("2\n");
		tmp = list->end;
		list->end = tmp->prev;
		if(list->end != NULL)
			list->end->next = NULL;
		//printf("3\n");
	}
	else {
		tmp = dll_getData(list, pos);
		if(tmp->prev != NULL)
			tmp->prev->next = tmp->next;
		if(tmp->next != NULL)
			tmp->next->prev = tmp->prev;	
	}
	list->size--;
	//printf("removed: %d %d %d %d %d\n", pos, (int)tmp, (int)tmp->value, (int)tmp->prev, (int)tmp->next);
	free(tmp);
	return 1;
}

void dll_print(DoubleLinkedList* list)
{
	Data *tmp;
	int pos;
	if(list == NULL)
	{
		printf("La list est NULL\n");
		return;
	}
	printf("Nombre d'éléments: %d\n", list->size);
	tmp = list->begin;
	pos = 0;
	while(tmp != NULL)
	{
		printf("%d %d %d %d %d\n", pos, (int)tmp, (int)tmp->value, (int)tmp->prev, (int)tmp->next);
		tmp = tmp->next;
		++pos;
	}
}

int dll_size(DoubleLinkedList* list)
{
	if(list == NULL)
		return -1;

	else
		return list->size;
}

void* dll_get(DoubleLinkedList* list, unsigned int pos)
{
	Data *tmp = dll_getData(list, pos);
	if(tmp == NULL)
		return NULL;

	return tmp->value;
}

Data* dll_getData(DoubleLinkedList* list, unsigned int pos)
{
	Data *tmp;
	int curr = 0;
	if(list == NULL || pos >= list->size)
		return NULL;

	tmp = list->begin;
	while(curr < pos)
	{
		tmp = tmp->next;
		curr++;
	}

	return tmp;
}


void dll_delete(DoubleLinkedList* list)
{
	if(list == NULL)
		return;

	freeData(list->begin);
	list->begin = NULL;
	list->end = NULL;
	free(list);
	list = NULL;
}

