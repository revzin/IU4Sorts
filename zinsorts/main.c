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
//#define MAIN_MODE_INTERACTIVE 
#define MAIN_MODE_PROFILE

int main(int argc, char** argv) {
	int rc;

	printf("Sorting Algorithms Team Assigment --- \n \t by G. Revzin, D. Feoktistov, P. Denisik & P. Monchakovskaya (IU4-32).\n");

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

	printf("\n \t Interactive sorting mode\n");
	for (;;) {
		if (need_init) {
			int_array = malloc(sizeof(int) * 25);
			int_array_capacity = 25;
			int_array_len = 0;
			need_init = 0;
			printf("Input an array to sort: ");
		}
		// ������ �� ���������� �������
		scanf(" %s", input_buf);

		// ���� exit, �������
		if (!strncmp(input_buf, "exit", MAX_STRING_LEN)) {
			free(int_array);
			break;
		}

		// ������� ������� �����
		buf_int = (int) strtol(input_buf, &pEnd, 10);
		if (pEnd == input_buf) {
			// �������, �����
			free(int_array);
			int_array_len = 0;
			need_init = 1;
			printf("\n");
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
			//SRT_sort_heap(int_array, sizeof(int), int_array_len, CMP_CompareInts, 1);
			SRT_sort_bubble(int_array, sizeof(int), int_array_len, CMP_CompareInts, 1);
			printf("Sorted array: ");
			for (i = 0; i < int_array_len; ++i) printf("%d ", int_array[i]);
			printf("\n");
			need_init = 1;
		} else {
			continue;
		}
	}

	return 0;
} 

int MAIN_ProfileMode(int argc, char** argv) {
	char input_buf[MAX_STRING_LEN], filename[MAX_STRING_LEN];
	int n_maxElems, n_minElems;

	char* pEnd;
	const int SELSORT_BUBBLE = 0;
	const int SELSORT_HEAP = 1;

	int selected_sort = -1;
	
	// �����: ����� ���������� ������ ����������
	// ������ ��� ������ �������� ����������
	printf("\n \t Profile mode\n");
	for(;;) {

		// �������� ����������
		printf("\nWhich sort would you like to profile (\"bubble\" or \"heap\" or \"exit\")? ");
		scanf(" %s", input_buf);
		if (!strncmp("bubble", input_buf, MAX_STRING_LEN)) {
			selected_sort = SELSORT_BUBBLE;
		} else if (!strncmp("heap", input_buf, MAX_STRING_LEN)) {
			selected_sort = SELSORT_HEAP;
		} else if (!strncmp("exit", input_buf, MAX_STRING_LEN)) {
			break;
		} else continue;

array_dimensions_min:
		printf("Min array elements: ");
		scanf(" %s", input_buf);

		// ������� ������� �����
		n_minElems = (int) strtol(input_buf, &pEnd, 10);
		if (pEnd == input_buf) {
			goto array_dimensions_min;
		}

		if (n_minElems < 1) {
			goto array_dimensions_min;
		}
array_dimensions_max:
		printf("Max array elements: ");
		scanf(" %s", input_buf);

		n_maxElems = (int) strtol(input_buf, &pEnd, 10);
		if (pEnd == input_buf) {
			goto array_dimensions_max;
		}

		if (n_maxElems <= n_minElems) {
			goto array_dimensions_max;
		}

filename:
		printf("gnuplot & PNG file name: ");
		scanf(" %s", input_buf);
		if (!strlen(input_buf)) {
			goto filename;
		}
		printf ("Profiling...");

		if (selected_sort == SELSORT_BUBBLE) {
			PROF_PlotEfficiency(input_buf, SRT_sort_bubble, n_minElems, n_maxElems);
		} else {
			PROF_PlotEfficiency(input_buf, SRT_sort_heap, n_minElems, n_maxElems);
		}
		printf("Running gnuplot...");
		strcpy(filename, input_buf);
		memset(input_buf, 0, MAX_STRING_LEN);
		strcpy(input_buf, "gnuplot ");
		strcat(input_buf, filename);
		strcat(input_buf, ".plt");
		system(input_buf); // ���� gnuplot
		memset(input_buf, 0, MAX_STRING_LEN);
		strcpy(input_buf, "call ");
		strcat(input_buf, filename);
		strcat(input_buf, ".png");
		system(input_buf); // ��������� ����������
		printf("Done.");
	}
	return 0;
}

int MAIN_TestMode(int argc, char** argv){
	// �����: ����� ���������� ������ ������������
	// ����������� ��������: ��������� TST_TestSort(..), ������� �� ���������� � test.c
	return 0;
}