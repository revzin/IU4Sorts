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
//              ���������������� ������ ������� ������
 
// ���� - ������� ����������� ����������
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Windows.h>
 
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


void CtrlBreakHandler(int code);
 
int main(int argc, char** argv) {
        int rc;
 
        printf("Sorting Algorithms Team Assigment --- \n \t by G. Revzin, D. Feoktistov, P. Denisik & P. Monchakovskaya (IU4-32).\n");
		SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlBreakHandler, TRUE);

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
 
        const int SELSORT_BUBBLE = 0;
        const int SELSORT_HEAP = 1;
 
        int selected_sort = SELSORT_HEAP;
        /*
                �������� ������ �����. ���� �������� \n, ����� ����������� � ��������� ������������� ������.
                ���� �����-�� �� ����� �� ���������� ���������� � �����, ����������.
        */

        printf("\n \t Interactive sorting mode\n\n");
        printf("Type 'bubble' to use bubble sort, 'heap' - to use heapsort, 'exit' - to exit programm. Heapsort is used by default.\n");
        for (;;) {
                if (need_init) {
                        int_array = malloc(sizeof(int) * 25);
                        int_array_capacity = 25;
                        int_array_len = 0;
                        need_init = 0;
                        fflush(stdin);
                        printf("Input an array to sort: ");
                }
                // ������ �� ���������� �������
                scanf(" %s", input_buf);
 
                // ���� exit, �������
                if (!strncmp(input_buf, "exit", MAX_STRING_LEN)) {
                        free(int_array);
                        break;
                }
 
                if (!strncmp(input_buf, "bubble", MAX_STRING_LEN)) {
                        selected_sort = SELSORT_BUBBLE;
                }
 
                if (!strncmp(input_buf, "heap", MAX_STRING_LEN)) {
                        selected_sort = SELSORT_HEAP;
                }
               
 
                // ������� ������� �����
                buf_int = (int) strtol(input_buf, &pEnd, 10);
                if (pEnd == input_buf) {
                        // �������, �����
                        free(int_array);
                        int_array_len = 0;
                        need_init = 1;
                        fflush(stdin);
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
                        if (selected_sort == SELSORT_HEAP) {
                                SRT_sort_heap(int_array, sizeof(int), int_array_len, CMP_CompareInts, 1);
                        } else {
                                SRT_sort_bubble(int_array, sizeof(int), int_array_len, CMP_CompareInts, 1);
                        }
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
		int prc;
 
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
                        fflush(stdin);
                        goto array_dimensions_min;
                }
 
                if (n_minElems < 1) {
                        fflush(stdin);
                        goto array_dimensions_min;
                }
array_dimensions_max:
                printf("Max array elements: ");
                scanf(" %s", input_buf);
 
                n_maxElems = (int) strtol(input_buf, &pEnd, 10);
                if (pEnd == input_buf) {
                        fflush(stdin);
                        goto array_dimensions_max;
                }
 
                if (n_maxElems <= n_minElems) {
                        fflush(stdin);
                        goto array_dimensions_max;
                }
 
filename:
                printf("gnuplot & PNG file name: ");
                scanf(" %s", input_buf);
                if (!strlen(input_buf)) {
                        fflush(stdin);
                        goto filename;
                }
                printf ("Profiling...");
 
                if (selected_sort == SELSORT_BUBBLE) {
                       prc = PROF_PlotEfficiency(input_buf, SRT_sort_bubble, n_minElems, n_maxElems);
                } else {
                       prc = PROF_PlotEfficiency(input_buf, SRT_sort_heap, n_minElems, n_maxElems);
                }

				if (prc) {
					printf("PROF_PlotEfficiency FAILED with rc %d!! Aborting.\n", prc);
					system("pause");
					exit(1);
				}

                printf("Running gnuplot... ");
                strcpy(filename, input_buf);
                memset(input_buf, 0, MAX_STRING_LEN);
                strcpy(input_buf, "gnuplot ");
                strcat(input_buf, filename);
                strcat(input_buf, ".plt");
                system(input_buf); // ���� gnuplot
                memset(input_buf, 0, MAX_STRING_LEN);
                //strcpy(input_buf, "call ");
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
 int num;
 char ch[MAX_STRING_LEN];
 for(;;) {
           printf("Which sort function do you want to check:\n");
           printf("1: Heap sorting;\n");
           printf("2: Bubble sorting;\n");
       printf("3: Incorrect sorting function(identity function);\n");
       printf("0: Exit.\n");
           printf("Press cirtain number: ");
           scanf(" %s", ch);
           printf("\n");
           if (!strncmp("1", ch, MAX_STRING_LEN))  {
         num = TST_TestSort(SRT_sort_heap);
             if (num == 0) printf("Heap sorting is correct!\n");
             else printf("Heap sorting is incorrect!\n");
         printf("Number of failed tests: %d %s", num,"\n");
           } else if (!strncmp("2", ch, MAX_STRING_LEN)) {
                 num = TST_TestSort(SRT_sort_bubble);
             if (num == 0) printf("Bubble sorting is correct!\n");
             else printf("Bubble sorting is correct!\n");
                 printf("Number of failed tests: %d %s", num,"\n");
           } else if (!strncmp("3", ch, MAX_STRING_LEN)) {
                 num = TST_TestSort(SRT_inc_sort);
             if (num == 0) printf("Incorect sorting is correct! Damn that world\n");
             else printf("Incorrect sorting is incorrect! Very strange!\n");
                 printf("Number of failed tests: %d %s", num,"\n");
           } else if (!strncmp("0", ch, MAX_STRING_LEN)) {
                 break;
           } else { printf("Wrong input! Repeat, please.\n\n"); continue;}
     
           printf("\n");
 }
       
 return 0;
}


void CtrlBreakHandler(int code) {
	if (code == CTRL_C_EVENT || code == CTRL_BREAK_EVENT) {
		printf("\nCtrl-Break! Aborting...\n");
		system("pause");
		exit(-1);
	}
}

