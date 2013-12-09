#include "profile.h"

// Стандартные библиотеки
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdio.h>
#include <float.h> // DBL_MAX


// Винда
#ifdef WIN32
#include <Windows.h>
#else 
#error "Windows only!"
#endif


// Местное
#include "comp.h" // Для CMP_CompareInt

/* Вспомогательная функция, выделяет память и создаёт size рандомных интов */
int* AllocRandIntArray(int size); 

#define RUNS_PER_VALUE 10

// Здесь всё в микросекундах!
__int64 g_StartTime = -1;			// Тиков процессора в момента запуска PROF_StartProfile
__int64 g_LastElapsedTime = -1;		// Момент времени, который был при
									// последнем вызове PROF_GetTimeElapsedMSec()

// __int64 - то же, что и long long

double g_PCFreq = -1.0f;			// Тиков процессора в микросекнуду.
									// Для удобства сразу в double, потом всё равно делить.

/*
		QueryPerformanceCounter() считывает значение процессорного таймера --- строго говоря, количество
	тактов с момента запуска компьютера. Зная количество тиков таймера в секунду, можно профилировать 
	программы с довольно высокой точностью.
*/

void PROF_StartProfile() {
	__int64 li = 0; 
	srand( (unsigned int) time(NULL));

	QueryPerformanceFrequency((LARGE_INTEGER*) &li);
	if (!li) return;
	g_PCFreq = (double) li / 1000000.0f;

	QueryPerformanceCounter((LARGE_INTEGER*) &g_StartTime);
	g_LastElapsedTime = -1;
}

double	PROF_GetTimeElapsedMSec() {
	__int64 localCounterValue;
	if (g_StartTime == -1) { // Не начинали профайлинг
		return (-1.0f); // Вряд ли кто сочтёт это за чистую монету
	}
	else {
		QueryPerformanceCounter((LARGE_INTEGER*) &localCounterValue);
		if (!localCounterValue) return -1.0f;
		localCounterValue = localCounterValue - g_StartTime;	// Сколько времени набежало со старта?
		g_LastElapsedTime = localCounterValue;
		return ((double) localCounterValue) / g_PCFreq;
	}
}

double	PROF_GetDeltaTimeMSec() {
	__int64 localCounterValue;
	if (g_StartTime == -1) { // Не начинали профайлинг
		return (-1.0f); // Вряд ли кто сочтёт это за чистую монету
	}
	else {
		QueryPerformanceCounter((LARGE_INTEGER*) &localCounterValue);
		if (!localCounterValue) return -1.0f;
		localCounterValue = localCounterValue - g_LastElapsedTime;
		return ((double) localCounterValue) / g_PCFreq;
	}
}


double	PROF_StopProfile() {
	g_StartTime = -1;
	g_LastElapsedTime = -1;
	return PROF_GetTimeElapsedMSec();
}

double	PROF_ProfileSort(int nElems,
	void (*sort_function)(void* array, int elem_size, int array_len, 
			int (*compare_function)(void* pA, void* pB), int ascending), 
			int* arrayBuffer
	) 
{
	int i;
	double timeElapsed, locTimeElapsed;

	if (nElems < 0 || !sort_function) return -1.0f;

	for (i = 0; i < nElems; ++i)
		arrayBuffer[i] = rand();
	// Расписываем случайными интами память под массив для сортировки

	timeElapsed = DBL_MAX;
	/* Профилируем сортировку - лучший из N результатов */
	for (i = 0; i < RUNS_PER_VALUE; ++i) {
		PROF_StartProfile(); 
		sort_function((void*) arrayBuffer, sizeof(int), nElems, CMP_CompareInts, 0);
		locTimeElapsed = PROF_GetTimeElapsedMSec();
		PROF_StopProfile();
		if (locTimeElapsed < timeElapsed) timeElapsed = locTimeElapsed;
	}
	/* Допрофилировались */
	if (timeElapsed <= 0.0) return -1.0f;
	return timeElapsed;
}

/* Строчки для общения с gnuplot */
const char GNUPLOT_CmdSetTitle[] = "set title \"Complexity\"\n";
const char GNUPLOT_CmdSetXLabel[] = "set xlabel \"Number of elements in array\"\n";
const char GNUPLOT_CmdSetYLabel[] = "set ylabel \"Time (abstract units)\"\n";
const char GNUPLOT_CmdSetGrid[] = "set grid\n";
const char GNUPLOT_CmdSetPNG[] = "set term pngcairo\nset output \"%s\"\n"; 
									// Используем библиотеку cairo для png
const char GNUPLOT_CmdExit[] = "exit\n"; 
const char GNUPLOT_CmdDoPlot[] = "plot \"%s\" title \"\"\n";
const char GNUPLOT_FileTitle[] = "#elements \t time\n";
const char GNUPLOT_DataFormat[] = "%d \t %f\n";
const char GNUPLOT_DefaultDatafileName[] = "algo_complex.data";

int	PROF_PlotEfficiency(char* pszFileName,
	void (*sort_function)(void* array, int elem_size, int array_len, 
			/* Это всё один аргумент - указатель на ф-цию сортировки */	int (*compare_function)(void* pA, void* pB), int ascending),
			/* А эти два - третий и чётвертый */ int n_minElems, int n_maxElems) 
{
	FILE* data_out, *gnuplot_out;
	int i;
	double locValue;
	int* arrayBuffer;

	char stringbuf[255];

	if (!pszFileName || !sort_function || 
			n_minElems <= 0 || n_maxElems <= 0 || n_minElems >= n_maxElems) return 2;

	arrayBuffer = malloc(sizeof(int) * n_maxElems);

	if (!arrayBuffer) return 3;

	// Профилировка и запись файла с данными
	if (fopen_s(&data_out, GNUPLOT_DefaultDatafileName, "w+")) return 1; 
	fprintf_s(data_out, GNUPLOT_FileTitle);

	for (i = n_minElems; i < n_maxElems + 1; ++i) {
		locValue = PROF_ProfileSort(i, sort_function, arrayBuffer);
		fprintf_s(data_out, GNUPLOT_DataFormat, i, locValue);
	}

	fclose(data_out);

	strncpy(stringbuf, pszFileName, 255);
	strncat(stringbuf, ".plt", 255);

	// Запись файла с командами для GNUPLOT
	if (fopen_s(&gnuplot_out, stringbuf, "w+")) return 1; 
	fprintf_s(gnuplot_out,	GNUPLOT_CmdSetTitle);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdSetXLabel);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdSetYLabel);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdSetYLabel);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdSetGrid);

	strncpy(stringbuf, pszFileName, 255);
	strncat(stringbuf, ".png", 255);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdSetPNG, stringbuf);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdDoPlot, GNUPLOT_DefaultDatafileName);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdExit);
	fclose(gnuplot_out);

	free(arrayBuffer);

	return 0;
}


#ifdef _DEBUG
#include <Windows.h>
void PROF_StubTestSortImitator(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending) 
{
	Sleep(array_len * array_len / 100);
}
#endif


int* AllocRandIntArray(int size) {
	int i;
	int* mem;
	if (size < 1) return NULL;
	mem = malloc(size * sizeof(int));
	if (!mem) return NULL;
	for (i = 0; i < size; ++i)
		mem[i] = rand();
	return mem;
}

