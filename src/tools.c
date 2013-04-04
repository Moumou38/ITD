#include "tools.h"

void freeNode(Node** node){
	if(node == NULL)
		return;
	Node* curr = *node;
	*node = (*node)->next;
	free(curr);
}