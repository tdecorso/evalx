#ifndef H_DA
#define H_DA

#include <stdlib.h>

typedef struct {
    void* data;
    size_t count;
    size_t capacity;
    size_t element_size;
} da;

// Allocates a new array on the heap
da* da_alloc(size_t element_size, size_t capacity);

// Frees the array
void da_free(da* arr);

// Appends an element to the back of the array
void da_append(da* arr, const void* element);

// Pops last element from the array
void da_pop(da* arr, void* element);

// Get element of the array at given index
void da_get(da* arr, size_t index, void* element);

// Set element of the array at given index
void da_set(da* arr, size_t index, const void* element);

// Get current number of elements
size_t da_count(const da* arr);

// Get current capacity
size_t da_capacity(const da* arr);

#endif // H_DA
