#include <stdio.h>
#include <stdlib.h>
#include "./avltree.h"


int main(void) {
	struct avl_node* root = NULL;

	// Insert a million items.
	printf("Adding items...\n");
	for (int i = 0; i < 1000 * 1000; ++i) {
		void *data = malloc(sizeof(int));
		*((int*)data) = i;
		root = avl_insert(root, i, data);
	}
	printf("Done!\n\n");


	// Search for a particular key.
	int key = 789321;
	printf("Searching    %i...\n", key);
	struct avl_node* n = avl_search(root, key);

	// Print value.
	printf("Key:         %i\n", key);
	printf("Value:       %i\n", *(int *)n->data);
	printf("Tree height: %i\n", n->height);
	printf("Done!\n\n");
	return 0;
}
