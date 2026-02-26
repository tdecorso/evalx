#ifndef H_LIST
#define H_LIST

#include <stdlib.h>

typedef struct list_node {
    void* data;
    struct list_node* next;
    struct list_node* prev;
} list_node;

typedef struct list {
    list_node* root;
    list_node* tail;
    size_t count;
    size_t element_size;
} list;

// Allocates a new list_node on the heap
list_node* list_node_alloc(size_t element_size);

// Frees the list_node
void list_node_free(list_node* n);

// Allocates a new list on the heap
list* list_alloc(size_t element_size);

// Frees the list
void list_free(list* l);

// Adds an element to the front of the list
void list_push_front(list* l, const void* element);

// Adds an element to the back of the list
void list_push_back(list* l, const void* element);

// Pops the first element of the list
void list_pop_front(list* l, void* element);

// Pops the last element of the list
void list_pop_back(list* l, void* element);

// Returns element at given index
void list_get(list* l, size_t index, void* element);

// Returns current number of elements in the list
size_t list_count(list* l);

// Returns the pointer to the list_node at given index
list_node* list_node_at(list* l, size_t index);

// Removes element at given index
void list_remove_at(list* l, size_t index, void* element);

// Inserts element at given index
void list_insert_at(list* l, size_t index, void* element);


#endif // H_LIST
