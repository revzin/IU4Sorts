// sorts.h - ������� ����������
// �����

// �������� --- ������������ ����� - �� ����� ��� ���������� ������. 
// ��� ������ ���� � ��������������� *.c-�����


// ����������� �������


// ������� �������
#include "comp.h"


void SRT_sort_pyramid(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending);
/*	������������� ���������� ������������� ���� ������
	array		-	��������� �� ������ ��� ����������
	elem_size	-	������ ������ �������� � ������ (����. sizeof(int))
	array_len	-	����� ����� �������
	int (*compare_function)(void* pA, void* pB) -
				-	��������� �� �������, ������������ ��� �������� ��� ����������.
					�������� �� ���������.
					������ ��������� 1, ���� *pA >= *pB � 0 � ��������� ������.
					������� ������ � comp.h/comp.c.
	descending	-	1, ���� ������� ����������� �� ��������.
				-	0, ���� �� �����������.
*/

void SRT_sort_bubble(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending);
/*	����������� ���������� ������������� ���� ������
	array		-	��������� �� ������ ��� ����������
	elem_size	-	������ ������ �������� � ������ (����. sizeof(int))
	array_len	-	����� ����� �������
	int (*compare_function)(void* pA, void* pB) -
				-	��������� �� �������, ������������ ��� �������� ��� ����������.
					�������� �� ���������.
					������ ��������� 1, ���� *pA >= *pB � - � ��������� ������.
					������� ������ � comp.h/comp.c.
	descending	-	1, ���� ������� ����������� �� ��������.
				-	0, ���� �� �����������.
*/


void SRT_sort_test_stub(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending);
// ��� �� ����� ���� �� ����������, � ������ �������, ������� ���������� ������ �����,
// � �������� ������� �������,
// ��� ��� ������������ ���������� ����� - �.