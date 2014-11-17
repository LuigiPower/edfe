#include "Hash.h"
#include "PriorityQueue.h"
#include <stdio.h>

#define HASH_PRIME_NUMBER 12289

typedef struct hash_table HashMap;

typedef struct priority_queue PriorityQ;
typedef struct priority_item PriorityItem;

int hash_func(void* key)
{
   int size = sizeof(int);

   unsigned char* ptr = (unsigned char*) key;

   int b = *ptr;

   for(int j = 2; j < size; j++)
   {
      b = ((b * 64) + *( ptr + j * size)) % HASH_PRIME_NUMBER;
   }

   return b;
}

void load_queue(PriorityQ* queue)
{
   for(int i = 0; i < 5; i++)
   {
      void* x = malloc(sizeof(int));
      *((int*)x) = i;
      pq_insert(queue, x, i);
      //printf("Item %d has value %d and priority %d\n", i, *x, i);
   }
}

int main(int argc, char* argv[])
{
/*
   HashMap* map = Hash(100, sizeof(int), sizeof(int), hash_func);

   int key = 10;
   int value = 25;

   int key2 = 11;
   int value2 = 203;

   insert(map, &key, &value);
   insert(map, &key2, &value2);

   int* found = (int*) lookup(map, &key2);

   printf("Found %d\n", *found);
*/
/*
   PriorityQ* queue = PriorityQueue(5);
   load_queue(queue);

   check_queue(queue);

   int i = 0;
   while(queue->dim > 0)
   {
      PriorityItem item = deleteMin(queue);
      //printf("Item%d: %d\n", i, *((int*)item.value));
      printf("Item %d: Priority=%d Value=%d Pos=%d\n", i, item.priority, *((int*)item.value), item.pos);
      i++;
   }
*/
   return 0;
}

