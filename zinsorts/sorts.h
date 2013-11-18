// sorts.h - функции сортировки
// Программист - Денис

// Стандартные инклюды


// Местные инклюды
#include "comp.h"


void sort_pyramid(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending);
/*	Пирамидальная сортировка произвольного типа данных
	array		-	указатель на массив под сортировку
	elem_size	-	размер одного элемента в байтах (напр. sizeof(int))
	array_len	-	длина всего массива
	int (*compare_function)(void* pA, void* pB) -
				-	указатель на функцию, сравнивающую два элемента под сортировку.
					Передача по указателю.
					Должна возраащть 0, если *pA >= *pB и 1 в противном случае.
					Примеры смотри в comp.h/comp.c.
	descending	-	1, если следует сортировать по убыванию.
				-	0, если по возрастанию.
*/

void sort_bubble(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending);
/*	Пузырьковая сортировка произвольного типа данных
	array		-	указатель на массив под сортировку
	elem_size	-	размер одного элемента в байтах (напр. sizeof(int))
	array_len	-	длина всего массива
	int (*compare_function)(void* pA, void* pB) -
				-	указатель на функцию, сравнивающую два элемента под сортировку.
					Передача по указателю.
					Должна возраащть 0, если *pA >= *pB и 1 в противном случае.
					Примеры смотри в comp.h/comp.c.
	descending	-	1, если следует сортировать по убыванию.
				-	0, если по возрастанию.
*/
