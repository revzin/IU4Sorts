#include "comp.h"

int CMP_CompareInts(void* pA, void* pB) {
	int* a, *b;
	a = pA;
	b = pB;
	if (*a >= *b) return 1;
	else return 0;
}


int CMP_CompareFloats(void* pA, void* pB) {
	float* a, *b;
	a = pA;
	b = pB;
	if (*a >= *b) return 1;
	else return 0;
}
