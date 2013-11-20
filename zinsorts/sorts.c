#include "sorts.h"

#include <math.h>
#include <memory.h>
#include <malloc.h>

// ����� ������� ������� ���������� ������� ����������

// ��������������� �������, �������� src � dst
void _copy_elems(void* src, void* dst, int elem_size) {
	if (elem_size > 0) {
		memcpy(dst, src, elem_size);
	}
}

// ��������������� �������, ���������� A c B
void _swap_elems(void* a, void* b, int elem_size) {
	void* buf;
	if (elem_size > 0) {
		buf = malloc(elem_size);
		if (!buf) return;
		memcpy(buf, a, elem_size);	// buf = a
		memcpy(a, b, elem_size);	// a = b
		memcpy(b, buf, elem_size);	// b = buf
	}
}

void SRT_sort_pyramid(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) {
		// �����: ����� ���������� SRT_sort_pyramid...

}

void SRT_sort_bubble(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) {

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




void SRT_sort_test_stub(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) 
{
	int i;
	for (i = 0; i < array_len * array_len * array_len * array_len * array_len * array_len; ++i) {
		++i;
		--i;
		i = i * i / i / sqrt(i) / sqrt(i) / sqrt(i) / sqrt(i) / sqrt(i);
	}
}
