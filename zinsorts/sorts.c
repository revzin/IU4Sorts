#include "sorts.h"

// ����� ������� ������� ���������� ������� ����������

void SRT_sort_pyramid(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) {
		// �����: ����� ���������� SRT_sort_pyramid...

}

void SRT_sort_bubble(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) {
		// �����: ����� ���������� SRT_sort_bubble...
}
	/* ���������� ���������� ������� ������������. 
	�� ����, ��, ��� ������ ������ ��� ������� - ������������ ������������ �������� � ���������� ��������������� ������?*/

/* ���� ���� ��� � ������������ compare_function ���������, �� ��
	��� ��� ��������� �� �������� � sorts.h:
	- ������ - ��� ��������� �� ������, ������� ����� �����������
	- ������ - ������ �������� � �������
	- ������ - ����� ����� �������
	- �������� - ������� ��� ��������� ��������� ����� � �����. 
	��������, ��� � � ���� ������������:
	int* ints = malloc(sizeof(int) * 25);
	for (int i = 0; i < 25; ++i)
		ints[i] = rand(); // ��������� �������
	SRT_sort_bubble(ints, sizeof(int), 25, CMP_CompareInts); // ������������� - �.
*/
