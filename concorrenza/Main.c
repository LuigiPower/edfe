#include "Car.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int direzioni [10] = {0,0,0,1,1,0,1,0,1,0};
   Monitor m;
   m.e.v = 1;

   int i = 0;

   while( i < 10 )
   {
      printf("Starting process %d\n", i);
      start(&m, direzioni[i]);
     // sleep(1);
      i++;
   }
}
