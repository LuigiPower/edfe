#include "Semaphore.h"
#include <stdio.h>

void P(Semaphore* s)
{
   printf("P() called: %d\n", s->v);
   while(s->v < 1)
   {
      printf("waiting...\n");
   }
   s->v = s->v - 1;
}

void V(Semaphore* s)
{
   s->v = s->v + 1;
}

