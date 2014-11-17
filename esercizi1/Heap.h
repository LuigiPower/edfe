#ifndef HEAP__H__
#define HEAP__H__
#include <stdlib.h>

int l(int i);
int r(int i);
int p(int i);

void swap(void* one, void* two, int el_size);
void minHeapRestore(void* a, int i, int dim, int el_size, int(*compare)(void* one, void* two));

void heapBuild(void* a, int n, int el_size, int(*compare)(void* one, void* two));

void heap_sort(void* a, int n, int el_size, int(*compare)(void* one, void* two));

#endif
