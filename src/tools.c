#include "tools.h"

void freeNode(Node* node)
{
	if(node == NULL)
		return;

	freeNode(node->next);
	free(node);
}

void freeList(Node** node){
	if(node == NULL || *node == NULL)
		return;

	freeNode(*node);
}
