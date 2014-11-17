#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "PathFinding.h"

/**
 * author: federicogiuggioloni
 *
 *
 */
int main(int argc, char* argv[])
{
   int map_width = 0;
   int map_height = 0;
   int i, j, k;
   int obs_s_x;
   int obs_e_x;
   int obs_s_y;
   int obs_e_y;

   Point start;
   Point goal;

   if(argc >= 7)
   {
      //Names are inverted...
      map_height = atoi(argv[1]);
      map_width = atoi(argv[2]);
      start.y = atoi(argv[3]);
      start.x = atoi(argv[4]);
      goal.y = atoi(argv[5]);
      goal.x = atoi(argv[6]);
   }
   else
   {
      printf("Usage: PathFind map_width map_height start_x start_y goal_x goal_y [obstacle_start_x obstacle_end_x obstacle_start_y obstacle_end_y...]");
      return 13;
   }

   //Code block to support older versions of the c standard
   //(initializing a variable in the middle of a block is not
   //allowed)
   {
      int map[map_width][map_height];

      for(i = 0; i < map_width; i++)
      {
         for(j = 0; j < map_height; j++)
         {
            map[i][j] = 0;
         }
      }

      for(i = 7; i < argc; i+=4)
      {
         obs_s_x = atoi(argv[i]);
         obs_e_x = atoi(argv[i+1]);
         obs_s_y = atoi(argv[i+2]);
         obs_e_y = atoi(argv[i+3]);

         for(j = obs_s_x; j < obs_e_x; j++)
         {
            for(k = obs_s_y; k < obs_e_y; k++)
            {
               map[j][k] = -1;
            }
         }
      }

/* Test cases
      for(i = 0; i < 30; i++)
      {
         map[i][5] = -1;
      }

      for(i = 2; i < 28; i++)
      {
         map[6][i] = -1;
      }

      for(i = 2; i < 28; i++)
      {
         map[i][6] = -1;
      }
*/

      struct list* best_path = a_star(map_width, map_height, map, start, goal);

      struct list* p = head(best_path);
      printf("\nPath calculated. Result:\n");
      if(p == NULL)
      {
         printf("NULL");
      }
      else
      {
         printf("\nPoint\t|\tX\t|\tY:\n");
         i = 0;
         while(!finished(best_path, p))
         {
            printf("%d\t|\t%d\t|\t%d\n", i, ((Point*)p->value)->x, ((Point*)p->value)->y);
            i += 1;
            p = next(p);
         }
      }
   }
   return 0;
}

