#include "Car.h"
#include <stdio.h>
#include <stdlib.h>

void start(Monitor* m, int mdir)
{
   if(fork())
   {

   }
   else
   {
      int dir = mdir;

      printf("Cerco di entrare in %d\n", dir);
      entra(m, dir);
      sleep(2);
      esci(m, dir);
      printf("Uscito in %d\n", dir);
      exit(0);
   }
}
