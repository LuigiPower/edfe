#include "Semaphore.h"

void P(Semaphore* s)
{
   while(s->v <= 0)
   {

   }
   s->v--;
}

void V(Semaphore* s)
{
   s->v++;
}

