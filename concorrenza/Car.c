#include "Car.h"
#include <stdio.h>
#include <stdlib.h>

void start(Monitor* m, int mdir)
{
   if(vfork())
   {

   }
   else
   {
      int dir = mdir;

      printf("\nCerco di entrare in %d\n", dir);
      entra(m, dir);
      printf("ENTRATO\n");
      sleep(2);
      printf("USCITO\n");
      esci(m, dir);
      printf("Uscito in %d\n", dir);
      exit(0);
   }
}
