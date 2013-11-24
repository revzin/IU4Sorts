#include "test.h"
#include "comp.h"
#include "malloc.h"
 
// Ниже приведены три эталонных сортировки.
//      - Первая (g_AlreadySortedReference) уже отсортирована и сортировки не требует,
//      - Вторая (g_NeedsReversal) отсортирована, но в обратную сторону - требуется обращение,
//      - Третья (g_GeneralCase) представляет более общий вариант.
 
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
	int num = 0;
	int i;
	int check;
	int* need_sort_mass;
	need_sort_mass = malloc( sizeof(int) * 10 );
	check = 0;
	for (i = 0; i < 10; i ++){
		*(need_sort_mass+i) = g_AlreadySortedReference.initialArray[i];        
	}
	sort_function(need_sort_mass, sizeof(int), 10, CMP_CompareInts, 1);

	for(i = 0; i < 10; i ++)
		if (*(need_sort_mass+i) != g_AlreadySortedReference.sortedArray[i]){
			check = 1;
			break;                    
		};        
	if (check == 1) num += 1;

	for(i = 0; i < 10; i ++){
		*(need_sort_mass+i) = g_ReverseSortedReference.initialArray[i];        
	}
	sort_function(need_sort_mass, sizeof(int), 10, CMP_CompareInts, 1);
	check = 0;
	for(i = 0; i < 10; i ++)
		if (*(need_sort_mass+i) != g_ReverseSortedReference.sortedArray[i]){
			check = 1;
			break;                    
		};        
	if (check) num += 1;

	for(i = 0; i < 10; i ++){
		*(need_sort_mass+i) = g_GeneralCase.initialArray[i];        
	}
	sort_function(need_sort_mass, sizeof(int), 10, CMP_CompareInts, 1);
	check = 0;
	for(i = 0; i < 10; i ++)
		if (*(need_sort_mass+i) != g_GeneralCase.sortedArray[i]){
			check = 1;
			break;                    
		};        
	if (check) num += 1;

	free(need_sort_mass);

	return num;
}