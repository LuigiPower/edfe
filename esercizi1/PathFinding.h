#ifndef PATHFINDING__H__
#define PATHFINDING__H__

typedef struct point
{
   int x;
   int y;
} Point;

extern struct list* a_star(int n, int m, int map[n][m], Point start, Point goal);

#endif
