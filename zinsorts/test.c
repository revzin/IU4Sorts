#include "test.h"

// ���� ��������� ��� ��������� ����������. 
//	- ������ (g_AlreadySortedReference) ��� ������������� � ���������� �� �������,
//	- ������ (g_NeedsReversal) �������������, �� � �������� ������� - ��������� ���������,
//	- ������ (g_GeneralCase) ������������ ����� ����� �������.

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
	TST_referenceSortRun* need_sort_mass = malloc(sizeof(int) * 10);;
	
    for(int i = 0; i < 10; i ++){
        *need_sort_mass[i] = g_AlreadySortedReference[0][i];        
    }
	sort_function(need_sort_mass, sizeof(int), 10, compare_function, 1);
	bool check = false;
	for(int i = 0; i < 10; i ++)
        if (*need_sort_mass[i] != g_AlreadySortedReference[1][i]){
            check = true;
            break;                    
        };        
    if (check) num += 1;
    
    for(int i = 0; i < 10; i ++){
        *need_sort_mass[i] = g_ReverseSortedReference[0][i];        
    }
	sort_function(need_sort_mass, sizeof(int), 10, compare_function, 1);
	check = false;
	for(int i = 0; i < 10; i ++)
        if (*need_sort_mass[i] != g_ReverseSortedReference[1][i]){
            check = true;
            break;                    
        };        
    if (check) num += 1;
    
    for(int i = 0; i < 10; i ++){
        *need_sort_mass[i] = g_GeneralCase[0][i];        
    }
	sort_function(need_sort_mass, sizeof(int), 10, compare_function, 1);
	check = false;
	for(int i = 0; i < 10; i ++)
        if (*need_sort_mass[i] != g_GeneralCase[1][i]){
            check = true;
            break;                    
        };        
    if (check) num += 1;
    
	return num;
}

