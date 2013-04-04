/* Double-Linked List: Structure de donnée */
/* */

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "list.h"

typedef struct doublelinkedlist {
	unsigned int size;
	Data* begin;
	Data* end;
} DoubleLinkedList;

// Créé et initialise une pile.
extern DoubleLinkedList* dll_init();

// Ajoute value à la liste à la position pos.
// Retourne 1 si l'élément a bien été ajouté, -1 sinon.
extern int dll_add(DoubleLinkedList* list, void* value, unsigned int pos);

// Ajoute value à la fin de la liste.
extern int dll_append(DoubleLinkedList* list, void* value);

// Ajoute value au début de la liste.
extern int dll_prepend(DoubleLinkedList* list, void* value);

// Supprime l'élément à la position pos.
// Retourne 1 si l'élément a bien été supprimé, -1 sinon.
extern int dll_remove(DoubleLinkedList* list, unsigned int pos);

// Affiche les informations de déboggage de la liste.
extern void dll_print(DoubleLinkedList* list);

// Retourne la taille de la liste.
extern int dll_size(DoubleLinkedList* list);

// Retourne l'élément à la position pos.
// Retourne NULL si pos <0 ou si pos >= size, ou si la liste est vide.
extern void* dll_get(DoubleLinkedList* list, unsigned int pos);

extern Data* dll_getData(DoubleLinkedList* list, unsigned int pos);

extern int dll_removeValue(DoubleLinkedList* list, unsigned int pos);

// Libère la liste.
extern void dll_delete(DoubleLinkedList* list);


#endif
