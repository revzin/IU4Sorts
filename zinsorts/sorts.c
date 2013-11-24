#include "sorts.h"

#include <math.h>
#include <memory.h>
#include <malloc.h>

// ����� ������� ������� ���������� ������� ����������


/* ��������������� ������� */
// ��������� �� i-��� ������� ����������� �������
__forceinline void* _ith_element(void* array, int i, int elem_size);
#define _ITH(x) _ith_element(array, (x), elem_size)	 // ���� ��������, ��� ������ ������� ������� ��� ������� �� ��������
													 // ���� �� ������ ������� _ith_element(array, �����-�� �����, elem_size)
													 // �� ����� �������� _ITH(x)
// ����������� ��������� ����������� �������
void _copy_elems(void* src, void* dst, int elem_size);
// ����� ��������� ����������� �������
void _swap_elems(void* a, void* b, int elem_size);
// ��������� ����������� �������
void _reverse(void* array, int array_len, int elem_size);
// ����������� �������
void _heap_heapify(void* array, int elem_size, int array_len, int (*compare_function)(void* pA, void* pB), int i);

/* ���������� �����  */ 
void SRT_sort_heap(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) {

	//_reverse(array, elem_size, array_len);
	int i;

	// ������������
	for (i = array_len / 2 - 1; i >= 0; --i) {
		_heap_heapify(array, elem_size, array_len, compare_function, i);
	}

	// ���������
	while (array_len > 1) {
		--array_len;
		_swap_elems(_ITH(0), _ITH(array_len), elem_size);
		_heap_heapify(array, elem_size, array_len, compare_function, 0);
	}

	if (!ascending) _reverse(array, elem_size, array_len);

}

void _heap_heapify(void* array, int elem_size, int array_len, int (*compare_function)(void* pA, void* pB), int i) {
	int maxChild = i;
	int childN;
	void* value = malloc(elem_size);
	
	// �������� �������� ��������
	_copy_elems(value, _ITH(i), elem_size);

	while (1) {
		childN = i * 2 + 1; // ����� �������

		// ����� ������� ������ ��������?
		if ((childN < array_len) && compare_function(_ITH(childN), value)) {
			maxChild = childN; // ����� �� ������������
		}

		++childN; // ������� � �������

		// ������ ������� ������ ��������?
		if ((childN < array_len) && compare_function(_ITH(childN), _ITH(maxChild)) ) {
			maxChild = childN; // ����� �� ������������
		}

		// ������� ������ ����� ��������? ����� �� ������.
		if (maxChild == i) break;

		 //������ ������� ������� � ������������:
		_copy_elems(_ITH(i), _ITH(maxChild), elem_size); // a[i] = a[maxChild]
		_copy_elems(_ITH(maxChild), value, elem_size); // a[maxChild] = value

		i = maxChild; // ������� � ������������� �������

	}
	free(value);	
}


/* ���������� ������ */
void SRT_sort_bubble(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) 
{
	int i, j, k;
	k = 0;
		
	for (i = 0; i < array_len; i++) {	
		for (j = 0; j < array_len - i - 1; j++)	{  // �������� i, ����� �� ������� ��������������� ��������
			// j-� ������� - �������
			k = j + 1; // k-� ������� - ���������
			if (ascending == 1 && compare_function(_ITH(j), _ITH(k)) == 1)  // ��������� �� �����������
				_swap_elems (_ITH(j), _ITH(k), elem_size); // ���� ������� ������� ������ ����������, ������ �� �������

			else if (ascending == 0 && compare_function(_ITH(j), _ITH(k)) == 0) // ��������� �� ��������
				_swap_elems (_ITH(j), _ITH(k), elem_size); // ���� ������� ������� ������ ����������, ������ �� �������
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


void _copy_elems(void* dst, void* src, int elem_size) {
	if (elem_size > 0) {
		memcpy(dst, src, elem_size);
	}
}

void _swap_elems(void* a, void* b, int elem_size) {
	void* buf;
	if (elem_size > 0) {
		buf = malloc(elem_size);
		if (!buf) return;
		memcpy(buf, a, elem_size);	// buf = a
		memcpy(a, b, elem_size);	// a = b
		memcpy(b, buf, elem_size);	// b = buf
		free(buf);
	}
}

void _reverse(void* array, int elem_size, int array_len) {
	int i;
	for (i = 0; i < array_len / 2; ++i) {
		_swap_elems(_ITH(i), _ITH(array_len - 1 - i), elem_size);
	}
}

__forceinline void* _ith_element(void* array, int i, int elem_size) {
	return (void*) ( (char*) array + elem_size * i);
}