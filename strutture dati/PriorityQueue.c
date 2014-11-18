#include "PriorityQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int l(int i)
{
   return 2 * i + 1;
}

int r(int i)
{
   return 2 * i + 2;
}

int max(int one, int two)
{
   return one > two ? one : two;
}

int padre(int i)
{
   return max(i/2 - 1, 0);
}

int is_empty(struct priority_queue* priority_queue)
{
   //printf("is_empty: %d\n", priority_queue->dim);
   return priority_queue->dim == 0;
}

int pq_equals(char* one, char* two, int size)
{
   int i;
   for(i = 0;i < size; i++)
   {
      if(*one != *two)
      {
         return 1;
      }
      one++;
      two++;
   }
   return 0;
}

int contains(struct priority_queue* queue, struct priority_item* item, int size)
{
   int i;
   for(i = 0; i < queue->dim; i++)
   {
      struct priority_item one = queue->h[i];
      struct priority_item two = *item;

      if(one.priority == two.priority && pq_equals(one.value, two.value, size))
      {
         return 1;
      }
   }
   return 0;
}

void minHeapRestore(struct priority_item* a, int i, int dim)
{
   int min = i;
   if(l(i) <= dim && a[l(i)].priority < a[min].priority)
   {
      min = l(i);
   }
   if(r(i) <= dim && a[r(i)].priority < a[min].priority)
   {
      min = r(i);
   }

   if(i != min)
   {
      swap_pri(a, i, min);
      minHeapRestore(a, min, dim);
   }
}

struct priority_queue* PriorityQueue(int n)
{
   struct priority_queue* queue = malloc(sizeof(struct priority_queue));
   queue->h = malloc(sizeof(struct priority_item) * n);
   queue->capacity = n;
   queue->dim = 0;
   for(int i = 0; i < n; i++)
   {
      queue->h[i].priority = INT_MAX;
      queue->h[i].value = NULL;
      queue->h[i].pos = -1;
   }
   return queue;
}

void* min(struct priority_queue* queue)
{
   if(queue->dim <= 0)
   {
      fprintf(stderr, "Trying to remove element from empty priority_queue");
      return NULL;
   }
   else
   {
      return queue->h;
   }
}

void check_queue(struct priority_queue* queue)
{
   int i;
   for(i = 0; i < queue->capacity; i++)
   {
      //printf("| %d, %d |", queue->h[i].priority, queue->h[i].pos);
   }
   //printf("Dimensions: %d\n", queue->dim);
}

struct priority_item* pq_item_insert(struct priority_queue* queue, struct priority_item* item)
{
   if(queue->dim >= queue->capacity)
   {
      fprintf(stderr, "priority_queue is FULL");
      return NULL;
   }
   else
   {
      queue->dim = queue->dim + 1;
      *(queue->h + queue->dim-1) = *item;
      int i = queue->dim-1;
      while(i > 0 && queue->h[i].priority < queue->h[padre(i)].priority)
      {
         swap_pri(queue->h, i, padre(i));
         i = padre(i);
         //printf("i = %d\t", i);
      }
      check_queue(queue);
      return queue->h + i;
   }
}


struct priority_item* pq_insert(struct priority_queue* queue, void* x, int p)
{
   if(queue->dim >= queue->capacity)
   {
      fprintf(stderr, "priority_queue is FULL");
      return NULL;
   }
   else
   {
      queue->dim = queue->dim + 1;
      struct priority_item* hdim = (queue->h + queue->dim-1);
      //printf("\nInserting %d as Value of priority %d\n", *((int*)x), p);
      //printf("Which has value %d\n", *((int*)x));
      hdim->value = x;
      hdim->priority = p;
      hdim->pos = queue->dim-1;
      int i = queue->dim-1;
      //printf("\ni = %d\t", i);
      while(i > 0 && queue->h[i].priority < queue->h[padre(i)].priority)
      {
         swap_pri(queue->h, i, padre(i));
         i = padre(i);
         //printf("i = %d\t", i);
      }
      check_queue(queue);
      return queue->h + i;
   }
}

void swap_pri(struct priority_item* h, int i, int j)
{
   struct priority_item t = h[i];
   h[i] = h[j];
   h[j] = t;
   h[i].pos = i;
   h[j].pos = j;
}

struct priority_item deleteMin(struct priority_queue* queue)
{
   if(queue->dim <= 0)
   {
      fprintf(stderr, "priority_queue is EMPTY");
      struct priority_item item = {.priority = INT_MAX, .value = NULL, .pos = -1};
      return item;
   }
   else
   {
      //check_queue(queue);
      swap_pri(queue->h, 0, queue->dim-1);
      queue->dim = queue->dim - 1;
      minHeapRestore(queue->h, 0, queue->dim-1);
      //check_queue(queue);
      return queue->h[queue->dim];
   }
}

void decrease(struct priority_queue* queue, struct priority_item* x, int p)
{
   x->priority = p;
   int i = x->pos;
   while(i > 0 && (queue->h[i]).priority < (queue->h[padre(i)]).priority)
   {
      swap_pri(queue->h, i, padre(i));
      i = padre(i);
   }
}

