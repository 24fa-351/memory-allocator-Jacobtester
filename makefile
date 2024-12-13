all: test_system test_custom

test_system: Test.c
	gcc -o test_system Test.c

test_custom: Test.c HeapAllocator.c
	gcc -o test_custom Test.c HeapAllocator.c -DUSE_CUSTOM_ALLOCATOR

clean:
	rm -f test_system test_custom
