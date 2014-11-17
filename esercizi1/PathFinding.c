/**
 * Author: Federico Giuggioloni
 *
 * a_star algorithm pseudo-code taken
 * from Wikipedia, first used it to write
 * a Java version, now translated it in C
 *
 * Uses an heuristic-based version of
 * Dijkstra's algorithm, choosing neighbors
 * based on a prediction (air distance
 * between the neighbor and the goal in this case)
 *
 * Implementation isn't optimal, Hash Tables shouldn't
 * be implemented using linear scanning and both
 * Hash and PriorityQueue are static structures based
 * on arrays, not dynamically allocated.
 *
 * In addition, Jump Point Search could be used to find
 * fewer candidate nodes to jump to (increasing
 * performance greatly)
 *
 * And still has some bugs (especially in edge cases)
 */
#define HASH_PRIME_NUMBER 12289

#include "PathFinding.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "List.h"
#include "PriorityQueue.h"
#include "Hash.h"

typedef struct hash_table HashMap;
typedef struct priority_queue Priority_Queue;
typedef struct priority_item PriorityItem;

int queueSize = 1024;
int hashSize = 1024;

int point_equals(Point one, Point two)
{
   return one.x == two.x && one.y == two.y;
}

int point_equals_ptr(void* one, void* two)
{
   Point* pone = (Point*) one;
   Point* ptwo = (Point*) two;

   printf("one: %d %d, two: %d %d\n", pone->x, pone->y, ptwo->x, ptwo->y);

   return point_equals(*pone, *ptwo);
}

int isWalkable(int x, int y, int n, int m, int map[n][m])
{
   if(x >= 0 && x < n && y >= 0 && y < m && map[x][y] >= 0)
   {
      return 1;
   }
   return 0;
}

/**
 * TODO FIXME!
 * came_from e' completamente rotto: implementazione della hash
 * ha dei problemi? Sopratutto la lookup sembra non funzionare
 * come deve (o la scan di conseguenza) a causa della funzione
 * is_null. Non trova i punti giusti nell'hashmap, nonostante
 * ci siano (o sembra ci siano)
 */
struct list* reconstruct_path(HashMap* came_from, Point* current)
{
   struct list* point_list = List();
   Point* iter = current;

   while(iter != NULL)
   {
      printf("Adding point %d %d\n", iter->x, iter->y);
      li_insert(head(point_list), iter);
      iter = lookup_custom(came_from, iter, point_equals_ptr);
   }

   return point_list;
}


/*
 * Shows the map for debugging purposes
 * */
void showMap(int n, int m, int map[n][m], Point start, Point goal, Point current)
{
   //Probably shouldn't use a check
   if(!DEBUG_SHOW_MAP) return;

   int i, j;
   char c;
   for(i = 0; i < n; i++)
   {
      for(j = 0; j < m; j++)
      {
         if(start.x == i && start.y == j)
            c = 'S';
         else if(goal.x == i && goal.y == j)
            c = 'G';
         else if(current.x == i && current.y == j)
            c = 'Q';
         else if(map[i][j] == 1)
            c = 'V';
         else if(map[i][j] == -1)
            c = '*';
         else c = '-';

         printf(" %c ", c);
      }
      printf("\n");
   }
   printf("\n");
}

int hash_func(void* key)
{
   int size = sizeof(int);

   unsigned char* ptr = (unsigned char*) key;

   int b = *ptr;

   for(int j = 2; j < size; j++)
   {
      b = ((b * 64) + *( ptr + j * size)) % HASH_PRIME_NUMBER;
   }

   return b;
}

/**
 * heuristic_cost_estimate
 * Air distance between start and goal
 */
int heuristic_cost_estimate(Point start, Point goal)
{
   int abs1 = abs(goal.x - start.x);
   int abs2 = abs(goal.y - start.y);
   return sqrt(abs1 * abs1 + abs2 * abs2);
}

/*
 * getNeighbors
 * Obtains a list of all nearby points
 * the list contains priorityitems that
 * contain a priority based on the chosen
 * heuristic
 */
struct list* getNeighbors(int n, int m, int map[n][m], Point* current, Point* goal, HashMap* g_score, HashMap* f_score)
{
   int x = current->x-1;
   int y = current->y-1;
   struct list* lista = List();
   int i, j;
   int possibleX, possibleY;
   int* f;
   int g_s;

   //printf("getNeighbors: Starting\n");

   for(i = 0; i < 3; i++)
   {
      for(j = 0; j < 3; j++)
      {
         possibleX = x + i;
         possibleY = y + j;

         //printf("getNeighbors: Testing %d %d for walkableness\n", possibleX, possibleY);


         if(isWalkable(possibleX, possibleY, n, m, map))
         {
            Point* punto = malloc(sizeof(Point));
            punto->x = possibleX;
            punto->y = possibleY;

            f = malloc(sizeof(int));
            g_s = *((int*)lookup(g_score, current));

            *f = g_s + heuristic_cost_estimate(*punto, *goal);

            insert(f_score, punto, f);
            PriorityItem* item = malloc(sizeof(PriorityItem));
            item->priority = *f;
            item->value = punto;
            item->pos = 0;

            //printf("X: %d Y: %d", punto->x, punto->y);

            li_insert(lista, item);
         }
      }
   }

   return lista;
}

struct list* a_star(int n, int m, int map[n][m], Point start, Point goal)
{
   //printf("I'm actually executing!\n");
   hashSize = n*m;
   queueSize = hashSize;

   Priority_Queue* open_set = PriorityQueue(queueSize);
   HashMap* closed_set = Hash(hashSize, sizeof(Point), sizeof(char), hash_func);
   HashMap* came_from = Hash(hashSize, sizeof(Point), sizeof(Point), hash_func);

   HashMap* g_score = Hash(hashSize, sizeof(Point), sizeof(int), hash_func);
   HashMap* f_score = Hash(hashSize, sizeof(Point), sizeof(int), hash_func);

   int zero = 0;
   insert(g_score, &start, &zero);
   int h = 0 + heuristic_cost_estimate(start, goal);
   insert(f_score, &start, &h);

   PriorityItem* startItem = pq_insert(open_set, &start, h);
   struct list* neighbors;

   char* placeholder = malloc(sizeof(char));
   *placeholder = 0;

   while(!is_empty(open_set))
   {
      PriorityItem item = deleteMin(open_set);
      Point* current = (Point*) item.value;

      showMap(n, m, map, start, goal, *current);

      if(point_equals(*current, goal))
      {
         //Ho finito: ricostruisci la strada e ritornala
         showMap(n, m, map, start, goal, *current);  //Forse usare un puntatore alla mappa
         printf("%d %d : %d %d\n", current->x, current->y, goal.x, goal.y);
         return reconstruct_path(came_from, current);
      }

      insert(closed_set, current, placeholder);
      neighbors = getNeighbors(n, m, map, current, &goal, g_score, f_score);
      struct list* p = head(neighbors);

      while(!finished(neighbors, p))
      {
         PriorityItem* neighbor = ((PriorityItem*) p->value);
         Point* point = (Point*) (neighbor->value);

         map[point->x][point->y] = 1;

         if(lookup(closed_set, point) != NULL)
         {
            p = next(p);
            continue;
         }

         int tentative_g_score = *((int*) lookup(g_score, current)) + 1;

         int* ptr_val = (int*) lookup(g_score, point);
         int valore = 0;
         if(ptr_val != NULL)
            valore = *ptr_val;

         if(contains(open_set, neighbor, sizeof(Point)) || tentative_g_score > 0 || tentative_g_score < valore)
         {
            insert(came_from, point, current);
            printf("came_from + %d %d : %d %d\n", point->x, point->y, current->x, current->y);
            insert(g_score, point, &tentative_g_score);
            int value = tentative_g_score + heuristic_cost_estimate(*point, goal);
            insert(f_score, point, &value);
            if(!contains(open_set, neighbor, sizeof(Point)))
            {
               pq_insert(open_set, neighbor->value, value);
            }
            neighbor->priority = value;
         }

         p = next(p);

      }

      //showMap(n, m, map, start, goal);
   }

   return NULL;
}


