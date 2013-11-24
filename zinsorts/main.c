// main.c --- ����� �����
/* ����� ��������� ��� ��� ��� ������ ������� ������ ���������.
	1. �����: ������������� ����� ������, ����������� ������������ �������������� ������� ����� 
		� ����������� �� ����������. ���������� �� ��������� ������������� MAIN_MODE_INTERACTIVE
			
	2. �����: ����� ������������ ����������. ������ ����������������� �������� �������� ����� ������� ���������� � 
		������� ���������� � �� ��������� ������������. ���������� �� ��������� ������������� MAIN_MODE_TEST

	3. �����: ����� ����������� ����������. ������ �� �������� ������������� �������� ����������� ������ 
		��� ���������� �������� ��������� ��������� ��� ����� ����� ����������. ���������� �� ��������� ������������� MAIN_MODE_PROFILE
*/

// ���� ��������: �� ������ ������ ���������, ������� �� ��� ���������, �������, 
//		���������������� ������ ������� ������

// ���� - ������� ����������� ����������
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ���� - ������� �������
#include "profile.h"
#include "sorts.h"
#include "test.h"
#include "comp.h"

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
#define MAIN_MODE_INTERACTIVE 
//#define MAIN_MODE_PROFILE

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

#define MAX_STRING_LEN ((int) 255)


int MAIN_InteractiveMode(int argc, char** argv) {
	int* int_array;
	int int_array_len, int_array_capacity;
	int i;

	char input_buf[MAX_STRING_LEN];
	char* pEnd;
	int buf_int;

	int need_init = 1;

	/* 
		�������� ������ �����. ���� �������� \n, ����� ����������� � ��������� ������������� ������.
		���� �����-�� �� ����� �� ���������� ���������� � �����, ����������.
	*/

	for (;;) {
		if (need_init) {
			int_array = malloc(sizeof(int) * 25);
			int_array_capacity = 25;
			int_array_len = 0;
			need_init = 0;
			printf("\nInput an array to sort: ");
		}
		// ������ �� ���������� �������
		scanf(" %s", input_buf);

		// ���� exit, �������
		if (!strncmp(input_buf, "exit", MAX_STRING_LEN)) {
			break;
		}

		// ������� ������� �����
		buf_int = (int) strtol(input_buf, &pEnd, 10);
		if (pEnd == input_buf) {
			// �������, �����
			free(int_array);
			int_array_len = 0;
			need_init = 1;
			continue;
		}
		
		if (int_array_len == int_array_capacity) {
			// ������ �� �������
			int_array = realloc(int_array, int_array_capacity * 2);
			int_array_capacity *= 2;
		}

		int_array[int_array_len] = buf_int;
		int_array_len++;

		if ((char) getchar() == '\n') {
			// ���� ������ \n, ��������������� 
			// TODO: ����� ����������
			SRT_sort_heap(int_array, sizeof(int), int_array_len, CMP_CompareInts, 1);
			printf("Sorted array: ");
			for (i = 0; i < int_array_len; ++i) printf("%d ", int_array[i]);
			need_init = 1;
		} else {
			continue;
		}
	}

	return 0;
} 

int MAIN_ProfileMode(int argc, char** argv) {
	// �����: ����� ���������� ������ ����������
	// ������ ��� ������ �������� ����������
	puts("Testing PROF graph plot, please wait a little...");
	PROF_PlotEfficiency("gnuplot.plt", PROF_StubTestSortImitator, 1, 120);
	puts("Done!");
	system("pause");
	return 0;
}

int MAIN_TestMode(int argc, char** argv){
	// �����: ����� ���������� ������ ������������
	// ����������� ��������: ��������� TST_TestSort(..), ������� �� ���������� � test.c
	return 0;
}