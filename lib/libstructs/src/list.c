#include "../include/list.h"

List* list_init() 
{
	List* l = malloc(sizeof(List));
	if(l == NULL)
		return NULL;

	l->data = NULL;
	l->size = 0;
	return l;
}

int list_add(List* list, void* value, unsigned int pos)
{
	Data *tmp = NULL, *last = NULL, *add = NULL;
	unsigned int curr = 0;
	if(list == NULL || value == NULL) {
		return -1;
	}


	// Création du nouveau maillon
	add = malloc(sizeof(Data));
	if(add == NULL)
		return -1;
	add->value = value;
	add->next = NULL;

	// Recherche et ajout du maillon en bonne position.
	if(pos == 0) {
		add->next = list->data;
		list->data = add;
	}
	else if(pos >= list->size) {
		tmp = list_getData(list, list->size-1);
		tmp->next = add;
	}
	else {
		last = list_getData(list, pos-1);
		tmp = last->next;
		last->next = add;
		add->next = tmp;
	}
	
	list->size++;
	return 1;
}

int list_append(List* list, void* value)
{
	if(list == NULL)
		return -1;

	return list_add(list, value, list->size);
}

int list_prepend(List* list, void* value)
{
	if(list == NULL)
		return -1;

	return list_add(list, value, 0);
}

int list_remove(List* list, unsigned int pos)
{
	Data *tmp = NULL, *next = NULL, *last = NULL;
	unsigned int curr = 0;
	if(list == NULL || list->size <= pos)
		return -1;

	tmp = list->data;
	if(pos == 0) {
		list->data = tmp->next;
	} else {
		last = tmp;
		while(curr < pos) 
		{
			last = tmp;
			tmp = tmp->next;
			curr++;
		}
		last->next = tmp->next;
	}
	free(tmp);
	
	list->size--;
	return 1;
}

void list_print(List* list)
{
	Data *tmp;
	if(list == NULL)
	{
		printf("La list est NULL\n");
		return;
	}
	printf("Nombre d'éléments: %d\n", list->size);
	tmp = list->data;
	while(tmp != NULL)
	{
		printf("node: %p value: %p next: %p\n", tmp, tmp->value, tmp->next);
		tmp = tmp->next;
	}
}

int list_size(List* list)
{
	if(list == NULL)
		return -1;

	else
		return list->size;
}

void* list_get(List* list, unsigned int pos)
{
	Data *tmp = list_getData(list, pos);
	if(tmp == NULL)
		return NULL;

	return tmp->value;
}

Data* list_getData(List* list, unsigned int pos)
{
	Data *tmp;
	int curr = 0;
	if(list == NULL || pos >= list->size)
		return NULL;

	tmp = list->data;
	while(curr < pos)
	{
		tmp = tmp->next;
		curr++;
	}

	return tmp;
}

void list_foreach(List* list, void (*function)(void*))
{
	Data *tmp;
	if(list == NULL)
		return;

	tmp = list->data;
	while(tmp != NULL)
	{
		function(tmp->value);
		tmp = tmp->next;
	}	
}

void list_delete(List* list)
{
	if(list == NULL)
		return;

	freeData(list->data);
	list->data = NULL;
	free(list);
	list = NULL;
}

void freeData(Data* data)
{
	if(data == NULL)
		return;

	if(data->next != NULL)
		freeData(data->next);

	free(data);
}
