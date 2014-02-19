// profile.h --- ������� ��� ������ ������������� ����������� � ������ �������� �������� � Gnuplot
// �����
#include "common_typedef.h"


void	PROF_StartProfile();
// ������/���������� ������� �������

double	PROF_GetTimeElapsedMSec();
// ������ ���������� �����������, ���������� � ���������� ������ PROF_StartProfile();

double	PROF_GetDeltaTimeMSec();
// ���������� ���������� �����������, ���������� � ������� ���������� ������ GetTimeElapsedMSec

double	PROF_StopProfile();
// ��������� �������

double	PROF_ProfileSort(int nElems, sort_function sf, int* arrayBuffer);
// ����� �������, ���������� �� ���������� nElems ��������� �������� ����������, �������� ���������� *sort_function
// � arrayBuffer ��������� �������� ����� ��� ���������� array_len int-��

int	PROF_PlotEfficiency(char* pszFileName, sort_function sf, int n_minElems, int n_maxElems);
// ���������� ������� ��������� ��������� ������� ���������� *sort_function � ������� gnuplot
// pszFileName - �������� ����� gnuplot ��� ������ � �� ���������������� ����� PNG
// ������ �������� �� n_minElems �� n_maxElems � ���� pszFileName
// � ������ ������ ������������ 0


void PROF_StubTestSortImitator(void* array, int elem_size, int array_len, 
	compare_function cf);
// �������� ���������� � ������ ��������� ��������� "����������" ��� ������� ���������� �������� 
// � PROF_PlotEfficiency