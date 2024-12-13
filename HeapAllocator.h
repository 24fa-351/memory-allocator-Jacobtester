// HeapAllocator.h
#ifndef HEAP_ALLOCATOR_H
#define HEAP_ALLOCATOR_H

#include <stddef.h>
#include <sys/types.h>

void *heap_malloc(size_t size);
void heap_free(void *ptr);
void *heap_realloc(void *ptr, size_t size);
void *get_me_blocks(ssize_t how_much);

#endif // HEAP_ALLOCATOR_H