#ifndef H_TDS
#define H_TDS

#include <stdlib.h>

typedef struct {
    size_t count;
    size_t capacity;
} da_header_t;

// Allocates header and data for the dynamic array
#define da_alloc(ptr, cap)                                                         \
    do {                                                                           \
        da_header_t* header = malloc(sizeof(da_header_t) + cap * sizeof(*(ptr)));  \
        header->count = 0;                                                         \
        header->capacity = (cap);                                                  \
        (ptr) = (void*) (header + 1);                                              \
    } while (0);                                                                   \

// Frees allocated memory for dynamic array
#define da_free(ptr) \
    do { \
        free(da_header(ptr)); \
    } while (0);

// Pushes new item to the back of the array. Allocates new array if pointer is null.
#define da_push_back(ptr, item) \
    if (!(ptr)) da_alloc((ptr), 1); \
    do { \
        if (da_count(ptr) == da_capacity(ptr)) { \
            da_header_t* header = da_header(ptr); \
            size_t new_capacity = header->capacity * 2; \
            size_t new_size = sizeof(da_header_t) + new_capacity * sizeof(*(ptr)); \
            header = realloc(header, new_size);\
            (ptr) = (void*) (header + 1); \
            da_capacity(ptr) *= 2; \
        } \
        (ptr)[da_count(ptr)] = (item); \
        da_count(ptr)++; \
    } while (0); \

// Sets the numbers of elements of the array to zero
#define da_clear(ptr) \
    do { \
        da_header_t* h = da_header(ptr); \
        h->count = 0; \
    } while (0);


// Returns pointer to dynamic array header
#define da_header(ptr) ((da_header_t*) (ptr) - 1)

// Current number of elements in the array
#define da_count(ptr) (da_header(ptr)->count)

// Current capacity of the array
#define da_capacity(ptr) (da_header(ptr)->capacity)

#endif // H_TDS
