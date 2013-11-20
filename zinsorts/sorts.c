#include "sorts.h"

// ����� ������� ������� ���������� ������� ����������

void SRT_sort_pyramid(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) {
		// �����: ����� ���������� SRT_sort_pyramid...

}

void SRT_sort_bubble(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) {
		int i, j, k;
		if (ascending==1)
		{
			for (i=0; i<array_len; i++)
			{
				for (j=array_len-1; j>=i; j--)
				{
					if (compare_function(array [j], array [j+1])==1)
					{
						k=array[j];
						array[j]=array[j+1];
						array[j+1]=k; //swap
					}
				}
			}
		}
		else if (ascending==0)
		{
			for (i=0; i<array_len; i++)
			{
				for (j=array_len-1; j>=i; j--)
				{
					if (compare_function(array [j], array [j+1])==0)
					{
						k=array[j];
						array[j]=array[j+1];
						array[j+1]=k; //swap
					}
				}
			}
		}
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
