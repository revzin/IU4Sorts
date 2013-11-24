#include "test.h"
#include "comp.h"
#include "malloc.h"
 
// ���� ��������� ��� ��������� ����������.
//      - ������ (g_AlreadySortedReference) ��� ������������� � ���������� �� �������,
//      - ������ (g_NeedsReversal) �������������, �� � �������� ������� - ��������� ���������,
//      - ������ (g_GeneralCase) ������������ ����� ����� �������.
 
// ������ ������
const TST_referenceSortRun g_AlreadySortedReference =
{
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
};
 
// ������ ������
const TST_referenceSortRun g_ReverseSortedReference =
{
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
};
 
// ������ ������
const TST_referenceSortRun g_GeneralCase = {
        {3, 9, 6, 2, 8, 1, 5, 4, 10, 7},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
};
 
int TST_TestSort(void (*sort_function)(void* array, int elem_size, int array_len,
                                                                                        int (*compare_function)(void* pA, void* pB),
                                                                                        int ascending))
{
	// �����: ����������...
	// ���������, ������� TST_TestSort ������ �������� *sort_function �� ���� ��� ��������� �����������
	// ���� �������� ������, ������������ ��� (��������� ������� CompInt �� comp.h,
	// � ������ ��������� � �������� ��������������� ��������: ��. ����!
	// ������� ����� ���������� ����������� ������.
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