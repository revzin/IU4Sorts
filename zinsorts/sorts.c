#include "sorts.h"

// Здесь следует хранить реализации функций сортировки

void SRT_sort_pyramid(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) {
		// ДЕНИС: Здесь реализация SRT_sort_pyramid...

}

void SRT_sort_bubble(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) {
		// ДЕНИС: Здесь реализация SRT_sort_bubble...
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
