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
	return 0;
}

