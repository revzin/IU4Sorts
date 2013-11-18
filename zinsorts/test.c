#include "test.h"

// Ниже приведены три эталонных сортировки. 
//	- Первая (g_AlreadySortedReference) уже отсортирована и сортировки не требует,
//	- Вторая (g_NeedsReversal) отсортирована, но в обратную сторону - требуется обращение,
//	- Третья (g_GeneralCase) представляет более общий вариант.

// Первый эталон
const TST_referenceSortRun g_AlreadySortedReference = 
{
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
};

// Второй эталон
const TST_referenceSortRun g_ReverseSortedReference = 
{
	{10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
};

// Третий эталон
const TST_referenceSortRun g_GeneralCase = {
	{3, 9, 6, 2, 8, 1, 5, 4, 10, 7},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
};

int TST_TestSort(void (*sort_function)(void* array, int elem_size, int array_len, 
											int (*compare_function)(void* pA, void* pB), 
											int ascending)) 
{
	// ПАВЕЛ: реализация...
	// Напоминаю, функция TST_TestSort должна прогнать *sort_function по всем трём эталонным сортировкам
	// взяв исходный массив, отсортировав его (используй функцию CompInt из comp.h,
	// и сверив результат с эталонно отсортированным массивом: см. выше!
	// Вернуть нужно количество проваленных тестов.
	return 0;
}

