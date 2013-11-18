#include "profile.h"

void	PROF_StartProfile() {
	// РЕВЗИН: реализация
}
// Запуск/перезапуск отсчёта времени

float	PROF_GetTimeElaspedMSec() {
	// РЕВЗИН: реализация
	return 0.0;
}


void	PROF_StopProfile() {
	// РЕВЗИН: реализация
}

float	PROF_ProfileSort(int nElems,
	void (*sort_function)(void* array, int elem_size, int array_len, 
			int (*compare_function)(void* pA, void* pB), int ascending)
	) {
	// РЕВЗИН: реализация
	return 0.0;
}

void	PROF_PlotEfficiency(FILE* f,
	void (*sort_function)(void* array, int elem_size, int array_len, 
			int (*compare_function)(void* pA, void* pB), int ascending),
			int n_minElems, int n_maxElems) {

	// РЕВЗИН: реализация
}