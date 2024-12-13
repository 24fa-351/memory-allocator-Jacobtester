// Test.c
// Jacob Gray, CPSC 351
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Using to override malloc, free, and realloc
#ifdef USE_CUSTOM_ALLOCATOR
#include "HeapAllocator.h"
#define malloc(size) heap_malloc(size)
#define free(ptr) heap_free(ptr)
#define realloc(ptr, size) heap_realloc(ptr, size)
#endif

// Test 1: Simple Allocation
void run_test_1()
{
    printf("Running Test 1: Simple Allocation...\n");
    void *ptr = malloc(128);
    if (ptr)
    {
        printf("Test 1 Passed\n");
    }
    else
    {
        printf("Test 1 Failed\n");
    }
}

// Test 2: Allocation and Freeing
void run_test_2()
{
    printf("Running Test 2: Allocation and Freeing...\n");
    void *ptr = malloc(128);
    if (ptr)
    {
        free(ptr);
        printf("Test 2 Passed\n");
    }
    else
    {
        printf("Test 2 Failed\n");
    }
}

// Test 3: Reallocating memory
void run_test_3()
{
    printf("Running Test 3: Reallocating Memory...\n");
    void *ptr = malloc(128);
    if (ptr)
    {
        ptr = realloc(ptr, 256);
        if (ptr)
        {
            printf("Test 3 Passed\n");
        }
        else
        {
            printf("Test 3 Failed\n");
        }
    }
    else
    {
        printf("Test 3 Failed\n");
    }
}

// Test 4: Freeing again with a different size
void run_test_4()
{
    printf("Running Test 4: Freeing with a Different Size...\n");
    void *ptr = malloc(256);
    if (ptr)
    {
        free(ptr);
        printf("Test 4 Passed\n");
    }
    else
    {
        printf("Test 4 Failed\n");
    }
}

// Run all tests
void run_all_tests()
{
    run_test_1();
    run_test_2();
    run_test_3();
    run_test_4();
}

int main(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "-t") == 0)
    {
        int test_num = atoi(argv[2]);
        switch (test_num)
        {
        case 1:
            // Allocate memory
            run_test_1();
            break;
        case 2:
            // Free memory
            run_test_2();
            break;
        case 3:
            // Reallocate memory
            run_test_3();
            break;
        case 4:
            // Free memory, different size
            run_test_4();
            break;
        default:
            printf("Invalid test number\n");
        }
    }
    else
    {
        run_all_tests();
    }
    return 0;
}
