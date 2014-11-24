#include "Bridge.h"
#include <stdio.h>

void init()
{
   coda.c.v = 0;
   in_coda = 0;
   nauto = 0;
   dircor = 0;
}

void entra(Monitor* m, int d)
{
   printf("Cerco di entrare da %d, auto: %d, dircor: %d, in_coda: %d\n", d, nauto, dircor, in_coda);
   entry_mon(m);
   if((dircor == d) && (nauto != 0))
   {
      in_coda++;
      wait_mon(m, &coda);
   }
   dircor = d;
   nauto++;
   exit_mon(m);
   printf("Esco da %d, auto: %d, dircor: %d, in_coda: %d\n", d, nauto, dircor, in_coda);
}

void esci(Monitor* m, int d)
{
   printf("Cerco di entrare da %d, auto: %d, dircor: %d, in_coda: %d\n", d, nauto, dircor, in_coda);
   entry_mon(m);
   nauto--;

   if(nauto == 0)
   {
      while(in_coda > 0)
      {
         in_coda--;
         signal_mon(m, &coda);
      }
   }
   exit_mon(m);
   printf("Esco da %d, auto: %d, dircor: %d, in_coda: %d\n", d, nauto, dircor, in_coda);
}
