#include "sorts.h"

#include <math.h>
#include <memory.h>
#include <malloc.h>

// Здесь следует хранить реализации функций сортировки

// Вспомогательная функция, копирует src в dst
void _copy_elems(void* src, void* dst, int elem_size) {
	if (elem_size > 0) {
		memcpy(dst, src, elem_size);
	}
}

// Вспомогательная функция, обменивает A c B
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
		// ДЕНИС: Здесь реализация SRT_sort_pyramid...

}

void SRT_sort_bubble(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) {

}
	/* Количество аргументов немного демотивирует. 
	По идее, всё, что должны делать эти функции - обрабатывать возвращаемые значения и записывать отсортированный массив?*/

/* Если речь идёт о возвращаемых compare_function значениях, то да
	Так все аргументы же пояснены в sorts.h:
	- Первый - это указатель на массив, который нужно сортировать
	- Второй - размер элемента в массиве
	- Третий - длина всего массива
	- Четвёртый - функция для сравнения элементов между с собой. 
	Например, так я её могу использовать:
	int* ints = malloc(sizeof(int) * 25);
	for (int i = 0; i < 25; ++i)
		ints[i] = rand(); // Заполнили мусором
	SRT_sort_bubble(ints, sizeof(int), 25, CMP_CompareInts); // Отсортировали - Г.
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
