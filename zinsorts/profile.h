// profile.h --- ������� ��� ������ ������������� ����������� � ������ �������� �������� � Gnuplot
// �����


void	PROF_StartProfile();
// ������/���������� ������� �������

double	PROF_GetTimeElapsedMSec();
// ������ ���������� �����������, ���������� � ���������� ������ PROF_StartProfile();

double	PROF_GetDeltaTimeMSec();
// ���������� ���������� �����������, ���������� � ������� ���������� ������ GetTimeElapsedMSec

double	PROF_StopProfile();
// ��������� �������

double	PROF_ProfileSort(int nElems,
	void (*sort_function)(void* array, int elem_size, int array_len, 
			int (*compare_function)(void* pA, void* pB), int ascending)
	);
// ����� �������, ���������� �� ���������� nElems ��������� �������� ����������, �������� ���������� *sort_function

int	PROF_PlotEfficiency(char* pszFileName,
	void (*sort_function)(void* array, int elem_size, int array_len, 
			int (*compare_function)(void* pA, void* pB), int ascending),
			int n_minElems, int n_maxElems);
// ���������� ������� ��������� ��������� ������� ���������� *sort_function � ������� gnuplot
// pszFileName - �������� ����� gnuplot ��� ������ � �� ���������������� ����� PNG
// ������ �������� �� n_minElems �� n_maxElems � ���� pszFileName
// � ������ ������ ������������ 0


void PROF_StubTestSortImitator(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending);
// �������� ���������� � ������ ��������� ��������� "����������" ��� ������� ���������� �������� 
// � PROF_PlotEfficiency