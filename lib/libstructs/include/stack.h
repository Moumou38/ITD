/* Stack: Structure de données LIFO (Last in, First Out) */
/* */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct stack {
	unsigned int size;
	Data* first;
} Stack;

// Créé et initialise une pile.
extern Stack* stack_init();

// Ajoute value à la fin de la pile.
// Retourne 1 si l'élément a bien été ajouté, -1 sinon.
extern int stack_push(Stack* pile, void* value);

// Supprime le premier élément de la pile.
// Retourne 1 si l'élément a bien été supprimé, -1 sinon.
extern int stack_pop(Stack* pile);

// Retourne l'élément au sommet de la pile.
// NULL en cas d'erreur.
extern void* stack_peek(Stack* pile);

// Affiche le contenu de la pile. Déboggage.
extern void stack_print(Stack* pile);

// Retourne la taille de la pile.
extern int stack_size(Stack* pile);

// Supprime la pile.
extern void stack_delete(Stack* pile);

#endif
