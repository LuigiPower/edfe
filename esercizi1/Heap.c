#include "Heap.h"

int l(int i)
{
   return 2i;
}

int r(int i)
{
   return 2i + 1;
}

int p(int i)
{
   return i/2;
}

void swap(void* one, void* two, int el_size)
{
   unsigned char* three = malloc(el_size);

   unsigned char* cone = (unsigned char*) one;
   unsigned char* ctwo = (unsigned char*) two;

   for(int i = 0; i < el_size; i++)
   {
      *three = *ctwo;
      *ctwo = *cone;
      *cone = *three;

      three++;
      ctwo++;
      cone++;
   }
   three = three - el_size;

   free(three);
   three = NULL;
}

//Compare is a function that returns:
//negative number if one < two
//zero if one == two
//positive number if one > two
void minHeapRestore(void* a, int i, int dim, int el_size, int(*compare)(void* one, void* two))
{
   int min = i;
   if(l(i) <= dim && compare(a + el_size * l(i), a + el_size * min) < 0)
   {
      min = l(i);
   }
}

void heapBuild(void* a, int n, int el_size, int(*compare)(void*one, void*two))
{
   for(int i = n/2; i >= 1; i--)
   {
      minHeapRestore(a, i, n, el_size, compare);
   }
}

void heap_sort(void* a, int n, int el_size, int(*compare)(void* one, void* two))
{
   heapBuild(a, n, el_size, compare);
   for(int i = n; i >= 2; i--)
   {
      swap(a + el_size * i, a, el_size);
      minHeapRestore(a, 1, i-1, el_size, compare);
   }
}

