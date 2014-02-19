#include "sorts.h"

#include <math.h>
#include <memory.h>
#include <malloc.h>

// Здесь следует хранить реализации функций сортировки


/* Вспомогательные функции */
// Указатель на i-тый элемент обобщенного массива
__forceinline void* _ith_element(void* array, int i, int elem_size);
#define _ITH(x) _ith_element(array, (x), elem_size)	 // Было замечено, что больше никаким образом эту функцию не вызывают
													 // Если вы хотите нписать _ith_element(array, какой-то номер, elem_size)
													 // То можно написать _ITH(x)
// Копирование элементов обобщенного массива
void _copy_elems(void* src, void* dst, int elem_size);
// Обмен элементов обобщенного массива
void _swap_elems(void* a, void* b, int elem_size, void* buffer);
// Обращение обобщенного массива
void _reverse(void* array, int array_len, int elem_size, void* buffer);
// Кучификация массива
void _heap_heapify(void* array, int elem_size, int array_len, compare_function cf, int i, void* buffer);
/* Все эти функции хотят выделенную память размером elem_size в указателе buffer */


/* Сортировка кучей  */ 
void SRT_sort_heap(void* array, int elem_size, int array_len, 
	compare_function cf, int ascending) 
{
	void* buffer = malloc(elem_size);

	//_reverse(array, elem_size, array_len);
	int i;

	// Кучифицируем
	for (i = array_len / 2 - 1; i >= 0; --i) {
		_heap_heapify(array, elem_size, array_len, cf, i, buffer);
	}

	// Сохраним длинну массива в не нужной более i
	i = array_len;

	// Сортируем
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
	
	// Значение текущего элемента
	_copy_elems(buffer, _ITH(i), elem_size);

	while (1) {
		childN = i * 2 + 1; // Левый потомок

		// Левый потомок больше текущего?
		if ((childN < array_len) && cf(_ITH(childN), buffer)) {
			maxChild = childN; // Тогда он максимальный
		}

		++childN; // Перешли к правому

		// Правый потомок больше текущего?
		if ((childN < array_len) && cf(_ITH(childN), _ITH(maxChild)) ) {
			maxChild = childN; // Тогда он максимальный
		}

		// Текущий больше своих потомков? Тогда всё хорошо.
		if (maxChild == i) break;

		 //Меняем местами текущий с максимальным:
		_copy_elems(_ITH(i), _ITH(maxChild), elem_size); // a[i] = a[maxChild]
		_copy_elems(_ITH(maxChild), buffer, elem_size); // a[maxChild] = buffer

		i = maxChild; // Перешли к изменившемуся потомку

	}
}


/* Сортировка пузырём */
void SRT_sort_bubble(void* array, int elem_size, int array_len, 
	compare_function cf, int ascending) 
{
	int i, j, k;
	void* buffer;
	k = 0;
	buffer = malloc(elem_size);
	for (i = 0; i < array_len; i++) {	
		for (j = 0; j < array_len - i - 1; j++)	{  // Отнимаем i, чтобы не трогать отсортированные элементы
			// j-й элемент - текущий
			k = j + 1; // k-й элемент - следующий
			if (ascending == 1 && cf(_ITH(j), _ITH(k)) == 1)  // Сортируем по возрастанию
				_swap_elems (_ITH(j), _ITH(k), elem_size, buffer); // Если текущий элемент больше следующего, меняем их местами

			else if (ascending == 0 && cf(_ITH(j), _ITH(k)) == 0) // Сортируем по убыванию
				_swap_elems (_ITH(j), _ITH(k), elem_size, buffer); // Если текущий элемент больше следующего, меняем их местами
		}
	}
	free(buffer);
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