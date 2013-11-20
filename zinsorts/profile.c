#include "profile.h"

// ����������� ����������
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdio.h>


// �����
#ifdef WIN32
#include <Windows.h>
#else 
#error "Windows only!"
#endif


// �������
#include "comp.h" // ��� CMP_CompareInt

/* ��������������� �������, �������� ������ � ������ size ��������� ����� */
int* AllocRandIntArray(int size); 



// ����� �� � �������������!
__int64 g_StartTime = -1;			// ����� ���������� � ������� ������� PROF_StartProfile
__int64 g_LastElapsedTime = -1;		// ������ �������, ������� ��� ���
									// ��������� ������ PROF_GetTimeElapsedMSec()

// __int64 - �� ��, ��� � long long

double g_PCFreq = -1.0f;			// ����� ���������� � ������������.
									// ��� �������� ����� � double, ����� �� ����� ������.

/*
		QueryPerformanceCounter() ��������� �������� ������������� ������� --- ������ ������, ����������
	������ � ������� ������� ����������. ���� ���������� ����� ������� � �������, ����� ������������� 
	��������� � �������� ������� ���������.
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
	if (g_StartTime == -1) { // �� �������� ����������
		return (-1.0f); // ���� �� ��� ����� ��� �� ������ ������
	}
	else {
		QueryPerformanceCounter((LARGE_INTEGER*) &localCounterValue);
		if (!localCounterValue) return -1.0f;
		localCounterValue = localCounterValue - g_StartTime;	// ������� ������� �������� �� ������?
		g_LastElapsedTime = localCounterValue;
		return ((double) localCounterValue) / g_PCFreq;
	}
}

double	PROF_GetDeltaTimeMSec() {
	__int64 localCounterValue;
	if (g_StartTime == -1) { // �� �������� ����������
		return (-1.0f); // ���� �� ��� ����� ��� �� ������ ������
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
			int (*compare_function)(void* pA, void* pB), int ascending)
	) 
{
	int* randomIntArray;
	double timeElapsed; 

	if (nElems < 0 || !sort_function) return -1.0f;

	/* �������� ����� ��� ������ ����� ��� ���������� */
	randomIntArray = AllocRandIntArray(nElems);
	if (!randomIntArray) return -1.0f;

	/* ����������� ���������� */
	PROF_StartProfile(); 
	sort_function((void*) randomIntArray, sizeof(int), nElems, CMP_CompareInts, 0);
	timeElapsed = PROF_GetTimeElapsedMSec();
	PROF_StopProfile();
	/* ����������������� */

	free(randomIntArray);	
	/* ����������� ������� */
	
	if (timeElapsed <= 0.0) return -1.0f;
	return timeElapsed;
}

const char GNUPLOT_CmdSetTitle[] = "set title \"Spatial Complexity\"\n";
const char GNUPLOT_CmdSetXLabel[] = "set xlabel \"Number of elements in array\"\n";
const char GNUPLOT_CmdSetYLabel[] = "set ylabel \"Time (usec)\"\n";
const char GNUPLOT_CmdSetGrid[] = "set grid\n";
const char GNUPLOT_CmdDoPlot[] = "plot \"%s\" title \"\"\n";

const char GNUPLOT_FileTitle[] = "#elements \t time\n";
const char GNUPLOT_DataFormat[] = "%d \t %f\n";

const char GNUPLOT_DefaultDatafileName[] = "algo_complex.data";

int	PROF_PlotEfficiency(char* pszFileName,
	void (*sort_function)(void* array, int elem_size, int array_len, 
			/* ��� �� ���� �������� - ��������� �� �-��� ���������� */	int (*compare_function)(void* pA, void* pB), int ascending),
			/* � ��� ��� - ������ � ��������� */ int n_minElems, int n_maxElems) 
{
	FILE* data_out, *gnuplot_out;
	int i;
	double locValue;

	if (!pszFileName || !sort_function || 
			n_minElems <= 0 || n_maxElems <= 0 || n_minElems >= n_maxElems) return 2;

	// ������������ � ������ ����� � �������
	if (fopen_s(&data_out, GNUPLOT_DefaultDatafileName, "w+")) return 1; 
	fprintf_s(data_out, GNUPLOT_FileTitle);

	for (i = n_minElems; i < n_maxElems + 1; ++i) {
		locValue = PROF_ProfileSort(i, sort_function);
		fprintf_s(data_out, GNUPLOT_DataFormat, i, locValue);
	}
	fclose(data_out);

	// ������ ����� � ��������� ��� GNUPLOT
	if (fopen_s(&gnuplot_out, pszFileName, "w+")) return 1; 
	fprintf_s(gnuplot_out,	GNUPLOT_CmdSetTitle);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdSetXLabel);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdSetYLabel);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdSetYLabel);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdSetGrid);
	fprintf_s(gnuplot_out,  GNUPLOT_CmdDoPlot, GNUPLOT_DefaultDatafileName);
	fclose(gnuplot_out);

	return 0;
}


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

