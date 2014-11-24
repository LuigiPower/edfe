#ifndef __SEMAPHORE__H_
#define __SEMAPHORE__H_

typedef struct semaphore
{
   int v;
} Semaphore;

void P(Semaphore* s);

void V(Semaphore* s);

#endif
