#ifndef H_BST
#define H_BST

#include <stdlib.h>
#include <stdbool.h>

typedef struct bst_node {
    int data;
    struct bst_node* left;
    struct bst_node* right;
} bst_node;

typedef struct {
    bst_node* root;
    size_t count;
} bst;
 
// Allocates a BST on the heap
bst* bst_alloc();

// Allocates a bst node on the heap
bst_node* bst_node_alloc();

// Frees a bst node
void bst_node_free(bst_node* node);

// Inserts given value starting from given node
void bst_node_insert(bst_node* node, int value);

// Searches given value starting from given node
bool bst_node_search(bst_node* node, int value);

// Frees a BST
void bst_free(bst* tree);

// Inserts given value in the tree
void bst_insert(bst* tree, int value);

// Searches given value in the tree
bool bst_search(bst* tree, int value);

#endif // H_BST
