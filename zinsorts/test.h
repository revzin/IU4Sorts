// tests.h - ������������ ���������� �� �����������
// �����

// �������� --- ������������ ����� - �� ����� ��� ���������� ������. 
// ��� ������ ���� � ��������������� *.c-�����


#define TST_TEST_REF_SEQ_SIZE ((int) 10)
// ���������� ��������� ��� �������� �� ��������� ����������

// ��������� ��� ������������� ��������� ����������
typedef struct {
	int initialArray[TST_TEST_REF_SEQ_SIZE];
		// �������� ������
	int sortedArray[TST_TEST_REF_SEQ_SIZE];
		// �������� ��������������� ������
} TST_referenceSortRun;

// ����� ������������� ��� �����, ������� ������ ���� ��������

int TST_TestSort(void (*sort_function)(void* array, int elem_size, int array_len, 
											int (*compare_function)(void* pA, void* pB), 
											int ascending));
// �������, ����������� ������������ ��������� ����������, �������� ���������� *sort_function, �� ��������
// ����� ����������������� ��� ��������� ����������, ������� ����� ���������� � test.c
// TST_TestSort ������ �������� �������� �� ���� ��� ��������� �����������
// ����� �������� ��������, ��� � TST_TestSort ����� ���� ��������, ���� �������� �������:
// void (*sort_function)(void* array, int elem_size, int array_len, int (*compare_function)(void* pA, void* pB), int ascending)
// �� ��� - ����� ���� ��������� �� �������, �������� ���, ��� ����� ����� � sort.h
// TST_TestSort ���������� ����� ����������� ��������!

void SRT_inc_sort(void* array, int elem_size, int array_len, 
	int (*compare_function)(void* pA, void* pB), int ascending);
// ������� ������������ ����������



