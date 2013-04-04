#include <stdio.h>
#include <stdlib.h>

#include "../include/list.h"
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/doublelinkedlist.h"

typedef struct {
	int a1;
	char a2;
} A;

int main(void) {
	A* a = malloc(sizeof(A)), *b = malloc(sizeof(A)), *c = NULL;
	List* l = list_init();
	Stack* s = stack_init();
	Queue* q = queue_init();
	DoubleLinkedList* d = dll_init();
	printf("a: %d\nB: %d\nc: %d\n", (int)a, (int)b, (int)c);
	a->a1 = 1;
	a->a2 = 'c';
	b->a1 = 2;
	b->a2 = 'a';

	printf("\n=== LIST TEST ===\n");
	list_add(l, a, 0);
	list_append(l, b);
	list_remove(l, 0);
	list_print(l);	
	c = list_get(l, 0);
	printf("c: %d\n", (int)c);
	list_delete(l);

	printf("\n=== STACK TEST ===\n");
	stack_push(s, b);
	stack_push(s, a);
	stack_pop(s);
	stack_print(s);
	c = stack_peek(s);
	printf("c: %d\n", (int)c);
	stack_delete(s);

	printf("\n=== QUEUE TEST ===\n");
	queue_push(q, a);
	queue_push(q, b);
	queue_pop(q);
	queue_print(q);
	c = queue_peek(q);
	printf("c: %d\n", (int)c);
	queue_delete(q);

	printf("\n=== DOUBLE LINKED LIST TEST ===\n");
	dll_add(d, b, 0);
	dll_prepend(d, a);
	dll_remove(d, 1);
	dll_print(d);
	c = dll_get(d, 0);
	printf("c: %d\n", (int)c);
	dll_delete(d);

	free(a);
	free(b);
	return 0;
}
