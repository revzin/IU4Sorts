// main.c --- точка входа
/* Здесь находится код для трёх разных режимов работы программы.
	1. ДЕНИС: Интерактивный режим работы, позволяющий пользователю самостоятельно вводить числа 
		и производить их сортировку. Включается по директиве препроцессора MAIN_MODE_INTERACTIVE
			
	2. ПАВЕЛ: Режим тестирования сортировок. Должен автоматизированно провести проверку обеих функций сортировки и 
		вывести информацию о их надёжности пользователю. Включается по директиве препроцессора MAIN_MODE_TEST

	3. ГРИША: Режим профайлинга сортировок. Должен по заданным пользователем пределам подготовить данные 
		для построения графиков временной сложности для обеих наших сортировок. Включается по директиве препроцессора MAIN_MODE_PROFILE
*/

// Всем внимание: за каждый утёкший указатель, который не был освобождён, щелбаны, 
//		пропорциональные объёму утекшей памяти

// Сюда - инклюды стандартной библиотеки
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Сюда - местные инклюды
#include "profile.h"
#include "sorts.h"
#include "test.h"
#include "comp.h"

// Объявления функций режимов
int MAIN_InteractiveMode(int argc, char** argv);
int MAIN_ProfileMode(int argc, char** argv);
int MAIN_TestMode(int argc, char** argv);
// Реализации этих функций, господа программисты, просьба держать внизу файла

// В эти функции из main передаются параметры командной строки, если они вам понадобятся
// Функции должны возвращать 0, если всё прошло хорошо, и любой другой код, если
// не прошло

// Чтобы переключить режим, надо закомметить два ненужных режима и раскомментить нужный
//#define MAIN_MODE_TEST
#define MAIN_MODE_INTERACTIVE 
//#define MAIN_MODE_PROFILE

int main(int argc, char** argv) {
	int rc;
	// Запуск активного режима работы
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
		Вводится строка чисел. Если получено \n, числа сортируется и выводится сортированный массив.
		Если какое-то из чисел не получилось превратить в число, сбрасываем.
	*/

	for (;;) {
		if (need_init) {
			int_array = malloc(sizeof(int) * 25);
			int_array_capacity = 25;
			int_array_len = 0;
			need_init = 0;
			printf("\nInput an array to sort: ");
		}
		// Читаем до следующего пробела
		scanf(" %s", input_buf);

		// Если exit, выходим
		if (!strncmp(input_buf, "exit", MAX_STRING_LEN)) {
			break;
		}

		// Пробуем сделать число
		buf_int = (int) strtol(input_buf, &pEnd, 10);
		if (pEnd == input_buf) {
			// Нечисло, сброс
			free(int_array);
			int_array_len = 0;
			need_init = 1;
			continue;
		}
		
		if (int_array_len == int_array_capacity) {
			// Больше не влезает
			int_array = realloc(int_array, int_array_capacity * 2);
			int_array_capacity *= 2;
		}

		int_array[int_array_len] = buf_int;
		int_array_len++;

		if ((char) getchar() == '\n') {
			// Если дальше \n, останавливаемся 
			// TODO: выбор сортировки
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
	// ГРИША: здесь реализация режима профайлера
	// Сейчас тут всякие проверки профайлера
	puts("Testing PROF graph plot, please wait a little...");
	PROF_PlotEfficiency("gnuplot.plt", PROF_StubTestSortImitator, 1, 120);
	puts("Done!");
	system("pause");
	return 0;
}

int MAIN_TestMode(int argc, char** argv){
	// ПАВЕЛ: здесь реализация режима тестирования
	// Руководящее указание: используй TST_TestSort(..), которую ты реализовал в test.c
	return 0;
}