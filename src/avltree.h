#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdlib.h>

struct avl_node {
	int key;
	void *data;    
	int height;
	struct avl_node* left;
	struct avl_node* right;
};

struct avl_node* avl_node_new(int key, void *data) {
	struct avl_node* node;
	node = malloc(sizeof(*node));

	node->key    = key;
	node->data   = (void *) data;
	node->height = 1;
	node->left   = NULL;
	node->right  = NULL;

	return node;
}

int avl_height(struct avl_node* nd) {
	return nd ? nd->height : 0;
}

void avl_recalc_height(struct avl_node* nd) {
	int lh  = avl_height(nd->left);
	int rh  = avl_height(nd->right);
	int max = lh > rh ? lh : rh;

	nd->height = 1 + max;
}

struct avl_node* avl_rotate_right(struct avl_node* p) {
	struct avl_node* q;
	q        = p->left;
	p->left  = q->right;
	q->right = p;

	avl_recalc_height(p);
	avl_recalc_height(q);

	return q;
}

struct avl_node* avl_rotate_left(struct avl_node* p) {
	struct avl_node* q;
	q        = p->right;
	p->right = q->left;
	q->left  = p;

	avl_recalc_height(p);
	avl_recalc_height(q);

	return q;
}

struct avl_node* avl_balance(struct avl_node* nd) {
	avl_recalc_height(nd);

	// TODO: extract vars
	if (avl_height(nd->left) - avl_height(nd->right) == 2) {
		if (avl_height(nd->left->right) > avl_height(nd->left->left)) {
			nd->left = avl_rotate_left(nd->left);
		}
		return avl_rotate_right(nd);
	}
	else if (avl_height(nd->right) - avl_height(nd->left) == 2) {
		if (avl_height(nd->right->left) > avl_height(nd->right->right)) {
			nd->right = avl_rotate_right(nd->right);
		}
		return avl_rotate_left(nd);
	}

	return nd;
}

struct avl_node* avl_search(struct avl_node* nd, int key) {
	if (!nd)
		return NULL;

	if (key < nd->key) {
		return avl_search(nd->left, key);
	}
	else if (key > nd->key) {
		return avl_search(nd->right, key);
	}
	else {
		return nd;        
	}
}

struct avl_node* avl_insert(struct avl_node* nd, int key, void *data) {
	if (!nd)
		return avl_node_new(key, data);

	if (key < nd->key) {
		nd->left = avl_insert(nd->left, key, data);
	}
	else if (key > nd->key) {
		nd->right = avl_insert(nd->right, key, data);
	}
	else {
		nd->data = data;
	}

	return avl_balance(nd);
}

struct avl_node* avl_find_min(struct avl_node* nd) {
	if (nd->left != NULL)
		return avl_find_min(nd->left);
	else
		return nd;
}

struct avl_node* avl_remove_min(struct avl_node* nd) {
	if (nd->left == NULL)
		return nd->right;

	nd->left = avl_remove_min(nd->left);
	return avl_balance(nd);
}

struct avl_node* avl_remove_item(struct avl_node* nd, int key) {
	if (!nd)
		return NULL;

	if (key < nd->key) {
		nd->left = avl_remove_item(nd->left, key);
	}
	else if (key > nd->key) {
		nd->right = avl_remove_item(nd->right, key);
	}
	else {
		struct avl_node* l = nd->left;
		struct avl_node* r = nd->right;
		free(nd);

		if (r == NULL)
			return l;

		struct avl_node* m  = avl_find_min(r);
		m->right = avl_remove_min(r);
		m->left  = l;

		return avl_balance(m);
	}

	return avl_balance(nd);
}

void avl_node_free(struct avl_node* nd) {
	if (!nd)
		return;

	avl_node_free(nd->left);
	avl_node_free(nd->right);
	free(nd);
}
#endif
