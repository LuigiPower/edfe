#include "List.h"
#include <stdlib.h>

struct list* List()
{
   struct list* t = malloc(sizeof(struct list));
   t->pred = t;
   t->succ = t;
   return t;
}

int empty(struct list* list)
{
   return list->pred == list->succ && list->succ  == list;
}

struct list* head(struct list* list)
{
   return list->succ;
}

struct list* tail(struct list* list)
{
   return list->pred;
}

struct list* next(struct list* p)
{
   return p->succ;
}

struct list* prev(struct list* p)
{
   return p->pred;
}

int finished(struct list* list, struct list* p)
{
   //printf("Finished: %d\n", p == list);
   return p == list;
}

void* li_read(struct list* p)
{
   return p->value;
}

void li_write(struct list* p, void* value)
{
   p->value = value;
}

struct list* li_insert(struct list* p, void* v)
{
   struct list* t = List();
   t->value = v;
   t->pred = p->pred;
   t->pred->succ = t;
   t->succ = p;
   p->pred = t;
   return t;
}

struct list* li_remove(struct list* p)
{
   p->pred->succ = p->succ;
   p->succ->pred = p->pred;
   struct list* t = p->succ;
   free(p);
   return t;
}

