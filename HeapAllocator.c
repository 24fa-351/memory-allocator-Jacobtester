// HeapAllocator.c
// Jacob Gray, CPSC 351
#include "HeapAllocator.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEAP_SIZE 1024 * 1024 // 1MB

// Block structure
typedef struct Block
{
    size_t size;
    int free;
    struct Block *next;
} Block;

static void *heap_start = NULL;
static Block *free_list = NULL;

// Initialize the heap
void heap_init()
{
    heap_start = get_me_blocks(HEAP_SIZE);
    // Fail check
    if (heap_start == (void *)-1)
    {
        fprintf(stderr, "Failed to initialize heap.\n");
        exit(1);
    }

    free_list = (Block *)heap_start;
    free_list->size = HEAP_SIZE - sizeof(Block);
    free_list->free = 1;
    free_list->next = NULL;
}

// Find a free block
Block *find_free_block(size_t size)
{
    Block *current = free_list;
    while (current != NULL)
    {
        if (current->free && current->size >= size)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Split a block
void split_block(Block *block, size_t size)
{
    Block *new_block = (Block *)((char *)block + sizeof(Block) + size);
    new_block->size = block->size - size - sizeof(Block);
    new_block->free = 1;
    new_block->next = block->next;

    block->size = size;
    block->free = 0;
    block->next = new_block;
}

// Start of memory allocation
void *heap_malloc(size_t size)
{
    if (size <= 0)
    {
        return NULL;
    }
    if (!heap_start)
    {
        heap_init();
    }

    Block *block = find_free_block(size);
    if (block)
    {
        if (block->size >= size + sizeof(Block) + 1)
        {
            split_block(block, size);
        }
        else
        {
            block->free = 0;
        }
        memset((char *)block + sizeof(Block), 0, size);
        return (char *)block + sizeof(Block);
    }
    fprintf(stderr, "No suitable block found.\n");
    return NULL;
}

// Free memory
void heap_free(void *ptr)
{
    if (!ptr)
    {
        return;
    }

    Block *block = (Block *)((char *)ptr - sizeof(Block));
    block->free = 1;
}

// Reallocate memory
void *heap_realloc(void *ptr, size_t size)
{
    if (!ptr)
    {
        return heap_malloc(size);
    }

    Block *block = (Block *)((char *)ptr - sizeof(Block));
    if (block->size >= size)
    {
        return ptr;
    }
    void *new_ptr = heap_malloc(size);
    if (new_ptr)
    {
        memcpy(new_ptr, ptr, block->size);
        heap_free(ptr);
    }
    return new_ptr;
}

// Acquire a block of memory
void *get_me_blocks(ssize_t how_much)
{
    void *ptr = sbrk(0);
    // Fail check
    if (sbrk(how_much) == (void *)-1)
    {
        fprintf(stderr, "Failed to allocate memory with sbrk.\n");
        return (void *)-1;
    }
    return ptr;
}