// profile.h --- функции для оценок эффективности соритировок и вывода красивых графиков в Gnuplot
// ГРИША
#include "common_typedef.h"


void	PROF_StartProfile();
// Запуск/перезапуск отсчёта времени

double	PROF_GetTimeElapsedMSec();
// Чтение количества миллисекунд, набежавших с последнего вызова PROF_StartProfile();

double	PROF_GetDeltaTimeMSec();
// Возвращает количество миллисекунд, набежавших с момента последнего вызова GetTimeElapsedMSec

double	PROF_StopProfile();
// Остановка отсчёта

double	PROF_ProfileSort(int nElems, sort_function sf, int* arrayBuffer);
// Замер времени, требуемого на сортировку nElems элементов функцией сортировки, заданной указателем *sort_function
// В arrayBuffer требуется передать место под размещение array_len int-ов

int	PROF_PlotEfficiency(char* pszFileName, sort_function sf, int n_minElems, int n_maxElems);
// Подготовка графика временной сложности функции сортировки *sort_function в формате gnuplot
// pszFileName - название файла gnuplot для вывода и по совместительству файла PNG
// График строится от n_minElems до n_maxElems в файл pszFileName
// В случае успеха возвращается 0


void PROF_StubTestSortImitator(void* array, int elem_size, int array_len, 
	compare_function cf);
// Имитатор сортировки с наперёд известной временной "сложностью" для отладки построения графиков 
// в PROF_PlotEfficiency