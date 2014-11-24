#include "Car.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
   Monitor m;
   m.e.v = 1;

   int i = 0;

   while( i < 10 )
   {
      printf("Starting process %d\n", i);
      start(&m);
      sleep(1);
      i++;
   }
}
