#include "Car.h"
#include <stdio.h>
#include <stdlib.h>

void start(Monitor* m)
{
   if(fork())
   {

   }
   else
   {
      int dir = 0;

      printf("Cerco di entrare in %d\n", dir);
      entra(m, dir);
      sleep(2);
      esci(m, dir);
      printf("Uscito in %d\n", dir);
      exit(0);
   }
}
