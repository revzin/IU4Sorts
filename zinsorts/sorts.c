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
void _swap_elems(void* a, void* b, int elem_size, void* buffer);
// ��������� ����������� �������
void _reverse(void* array, int array_len, int elem_size, void* buffer);
// ����������� �������
void _heap_heapify(void* array, int elem_size, int array_len, compare_function cf, int i, void* buffer);
/* ��� ��� ������� ����� ���������� ������ �������� elem_size � ��������� buffer */


/* ���������� �����  */ 
void SRT_sort_heap(void* array, int elem_size, int array_len, 
	compare_function cf, int ascending) 
{
	void* buffer = malloc(elem_size);

	//_reverse(array, elem_size, array_len);
	int i;

	// ������������
	for (i = array_len / 2 - 1; i >= 0; --i) {
		_heap_heapify(array, elem_size, array_len, cf, i, buffer);
	}

	// �������� ������ ������� � �� ������ ����� i
	i = array_len;

	// ���������
	while (array_len > 1) {
		--array_len;
		_swap_elems(_ITH(0), _ITH(array_len), elem_size, buffer);
		_heap_heapify(array, elem_size, array_len, cf, 0, buffer);
	}

	if (!ascending) _reverse(array, elem_size, i, buffer);
	free(buffer);
}

void _heap_heapify(void* array, int elem_size, int array_len, compare_function cf, int i, void* buffer) 
{
	int maxChild = i;
	int childN;
	
	// �������� �������� ��������
	_copy_elems(buffer, _ITH(i), elem_size);

	while (1) {
		childN = i * 2 + 1; // ����� �������

		// ����� ������� ������ ��������?
		if ((childN < array_len) && cf(_ITH(childN), buffer)) {
			maxChild = childN; // ����� �� ������������
		}

		++childN; // ������� � �������

		// ������ ������� ������ ��������?
		if ((childN < array_len) && cf(_ITH(childN), _ITH(maxChild)) ) {
			maxChild = childN; // ����� �� ������������
		}

		// ������� ������ ����� ��������? ����� �� ������.
		if (maxChild == i) break;

		 //������ ������� ������� � ������������:
		_copy_elems(_ITH(i), _ITH(maxChild), elem_size); // a[i] = a[maxChild]
		_copy_elems(_ITH(maxChild), buffer, elem_size); // a[maxChild] = buffer

		i = maxChild; // ������� � ������������� �������

	}
}


/* ���������� ������ */
void SRT_sort_bubble(void* array, int elem_size, int array_len, 
	compare_function cf, int ascending) 
{
	int i, j, k;
	void* buffer;
	k = 0;
	buffer = malloc(elem_size);
	for (i = 0; i < array_len; i++) {	
		for (j = 0; j < array_len - i - 1; j++)	{  // �������� i, ����� �� ������� ��������������� ��������
			// j-� ������� - �������
			k = j + 1; // k-� ������� - ���������
			if (ascending == 1 && cf(_ITH(j), _ITH(k)) == 1)  // ��������� �� �����������
				_swap_elems (_ITH(j), _ITH(k), elem_size, buffer); // ���� ������� ������� ������ ����������, ������ �� �������

			else if (ascending == 0 && cf(_ITH(j), _ITH(k)) == 0) // ��������� �� ��������
				_swap_elems (_ITH(j), _ITH(k), elem_size, buffer); // ���� ������� ������� ������ ����������, ������ �� �������
		}
	}
	free(buffer);
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


__forceinline void _copy_elems(void* dst, void* src, int elem_size) {
	memcpy(dst, src, elem_size);
}

void _swap_elems(void* a, void* b, int elem_size, void* buffer) {
	memcpy(buffer, a, elem_size);	// buf = a
	memcpy(a, b, elem_size);	// a = b
	memcpy(b, buffer, elem_size);	// b = buf
}

void _reverse(void* array, int elem_size, int array_len, void* buffer) {
	int i;
	for (i = 0; i < array_len / 2; ++i) {
		_swap_elems(_ITH(i), _ITH(array_len - 1 - i), elem_size, buffer);
	}
}

__forceinline void* _ith_element(void* array, int i, int elem_size) {
	return (void*) ( (char*) array + elem_size * i);
}