#ifndef H_STACK
#define H_STACK

#include <stdbool.h>

#include "tds/da.h"

typedef struct {
    da* arr;
} stack;

// Allocates a new stack on the heap
stack* stack_alloc(size_t element_size, size_t capacity);

// Frees the stack
void stack_free(stack* s);

// Adds element to the top of the stack
void stack_push(stack* s, const void* element);

// Removes element from the top of the stack
void stack_pop(stack* s, void* element);

// Get element from the top without removing it
void stack_peek(stack* s, void* element);

// Get current number of items in the stack
size_t stack_count(stack* s);

// Checks if stack is empty
bool stack_is_empty(stack* s);

#endif // H_STACK
