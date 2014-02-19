

typedef int (*compare_function)(void* pA, void* pB);


typedef void (*sort_function)(void* array, int elem_size, int array_len, 
			compare_function, int ascending);