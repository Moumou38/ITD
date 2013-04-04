/* Queue: structure de donnée FIFO (First In, First Out) */
/* */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct queue {
	unsigned int size;
	Data* data;
	Data* last;
} Queue;

// Créé et initialise une queue
extern Queue* queue_init();

// Ajoute value à la fin de file.
// Retourne 1 si l'élément a bien été ajouté, -1 sinon.
extern int queue_push(Queue* file, void* value);

// Supprime le premier élément de la file.
// Retourne 1 si l'élément a bien été supprimé, -1 sinon.
extern int queue_pop(Queue* file);

extern void* queue_peek(Queue* file);

extern void queue_print(Queue* file);

extern int queue_size(Queue* file);

extern void queue_delete(Queue* file);

#endif
