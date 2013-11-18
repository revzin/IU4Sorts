// profile.h --- функции для оценок эффективности соритировок и вывода красивых графиков в Gnuplot
// ГРИША

// Ст. библиотека
#include <stdio.h>


void	PROF_StartProfile();
// Запуск/перезапуск отсчёта времени

float	PROF_GetTimeElaspedMSec();
// Чтение количества миллисекунд, набежавших с последнего вызова PROF_StartProfile();

void	PROF_StopProfile();
// Остановка отсчёта

float	PROF_ProfileSort(int nElems,
	void (*sort_function)(void* array, int elem_size, int array_len, 
			int (*compare_function)(void* pA, void* pB), int ascending)
	);
// Замер времени, требуемого на сортировку nElems элементов функцией сортировки, заданной указателем *sort_function

void	PROF_PlotEfficiency(FILE* f,
	void (*sort_function)(void* array, int elem_size, int array_len, 
			int (*compare_function)(void* pA, void* pB), int ascending),
			int n_minElems, int n_maxElems);
// Подготовка графика временной сложности функции сортировки *sort_function в формате gnuplot
// График строится от n_minElems до n_maxElems
// данные для Gnuplot следует запихнуть в файл f.