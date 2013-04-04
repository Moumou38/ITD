/* List: Structure de données */
/* */

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct data {
	void* value;
	struct data* next;
	struct data* prev;
} Data;

typedef struct list {
	unsigned int size;
	Data* data;
} List;

// Créé et initialise une pile.
extern List* list_init();

// Ajoute value à la liste à la position pos.
// Retourne 1 si l'élément a bien été ajouté, -1 sinon.
extern int list_add(List* list, void* value, unsigned int pos);

// Ajoute value à la fin de la liste.
extern int list_append(List* list, void* value);

// Ajoute value au début de la liste.
extern int list_prepend(List* list, void* value);

// Supprime l'élément à la position pos.
// Retourne 1 si l'élément a bien été supprimé, -1 sinon.
extern int list_remove(List* list, unsigned int pos);

// Affiche les informations de déboggage de la liste.
extern void list_print(List* list);

// Retourne la taille de la liste.
extern int list_size(List* list);

// Retourne l'élément à la position pos.
// Retourne NULL si pos <0 ou si pos >= size, ou si la liste est vide.
extern void* list_get(List* list, unsigned int pos);

extern Data* list_getData(List* list, unsigned int pos);

extern void list_foreach(List* list, void (*function)(void*));


// Libère la liste.
extern void list_delete(List* list);


extern void freeData(Data* data);

#endif
