// main.c --- ����� �����
/* ����� ��������� ��� ��� ��� ������ ������� ������ ���������.
	1. �����: ������������� ����� ������, ����������� ������������ �������������� ������� ����� 
		� ����������� �� ����������. ���������� �� ��������� ������������� MAIN_MODE_INTERACTIVE
			
	2. �����: ����� ������������ ����������. ������ ����������������� �������� �������� ����� ������� ���������� � 
		������� ���������� � �� ��������� ������������. ���������� �� ��������� ������������� MAIN_MODE_TEST

	3. �����: ����� ����������� ����������. ������ �� �������� ������������� �������� ����������� ������ 
		��� ���������� �������� ��������� ��������� ��� ����� ����� ����������. ���������� �� ��������� �������������																								MAIN_MODE_PROFILE
*/

// ���� ��������: �� ������ ������ ���������, ������� �� ��� ���������, �������, 
//		���������������� ������ ������� ������

// ���� - ������� ����������� ����������
#include <stdio.h>
#include <stdlib.h>

// ���� - ������� �������
#include "profile.h"
#include "sorts.h"
#include "test.h"

// ���������� ������� �������
int MAIN_InteractiveMode(int argc, char** argv);
int MAIN_ProfileMode(int argc, char** argv);
int MAIN_TestMode(int argc, char** argv);
// ���������� ���� �������, ������� ������������, ������� ������� ����� �����

// � ��� ������� �� main ���������� ��������� ��������� ������, ���� ��� ��� �����������
// ������� ������ ���������� 0, ���� �� ������ ������, � ����� ������ ���, ����
// �� ������

// ����� ����������� �����, ���� ����������� ��� �������� ������ � ������������� ������
//#define MAIN_MODE_TEST
//#define MAIN_MODE_INTERACTIVE 
#define MAIN_MODE_PROFILE

int main(int argc, char** argv) {
	int rc;
	// ������ ��������� ������ ������
#ifdef MAIN_MODE_INTERACTIVE
	rc = MAIN_InteractiveMode(argc, argv);
#elif defined MAIN_MODE_TEST
	rc = MAIN_TestMode(argc, argv);
#elif defined MAIN_MODE_PROFILE
	rc = MAIN_ProfileMode(argc, argv);
#else
	rc = -1;
#endif
	return rc;
}


int MAIN_InteractiveMode(int argc, char** argv) {
	// �����: ����� ���������� �������������� ������
	// ���, ����������, ��� ��������, ����� ���� ��� �������. :)
	return 0;
}

int MAIN_ProfileMode(int argc, char** argv) {
	// �����: ����� ���������� ������ ����������
	// ������ ��� ������ �������� ����������
	puts("Testing PROF graph plot, please wait a little...");
	PROF_PlotEfficiency("gnuplot.plt", SRT_sort_test_stub, 1, 120);
	puts("Done!");
	system("pause");
	return 0;
}

int MAIN_TestMode(int argc, char** argv){
	// �����: ����� ���������� ������ ������������
	// ����������� ��������: ��������� TST_TestSort(..), ������� �� ���������� � test.c
	return 0;
}