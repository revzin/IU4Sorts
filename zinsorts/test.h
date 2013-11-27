// tests.h - тестирование сортировок на вменяемость
// ПАВЕЛ

// Внимание --- заголовочные файлы - не место для реализаций функцй. 
// Они должны идти в соответствующие *.c-файлы


#define TST_TEST_REF_SEQ_SIZE ((int) 10)
// Количество элементов для проверки по эталонной сортировке

// Структура для представления эталонной сортировки
typedef struct {
	int initialArray[TST_TEST_REF_SEQ_SIZE];
		// Исходный массив
	int sortedArray[TST_TEST_REF_SEQ_SIZE];
		// Эталонно отсортированный массив
} TST_referenceSortRun;

// Всего предусмотрено три теста, которые должны быть пройдены

int TST_TestSort(void (*sort_function)(void* array, int elem_size, int array_len, 
											int (*compare_function)(void* pA, void* pB), 
											int ascending));
// Функция, выполняющая тестирование алгоритма сортировки, заданной указателем *sort_function, по эталонам
// Всего предусматривается три эталонных сортировки, которые можно посмотреть в test.c
// TST_TestSort должна провести проверку по всем трём эталонным сортировкам
// Прошу обратить внимание, что у TST_TestSort всего один аргумент, зато довольно длинный:
// void (*sort_function)(void* array, int elem_size, int array_len, int (*compare_function)(void* pA, void* pB), int ascending)
// всё это - всего лишь указатель на функцию, подобную той, что можно найти в sort.h
// TST_TestSort возвращает число проваленных проверок!

void SRT_inc_sort(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending);
// функция неправильной сортировки



