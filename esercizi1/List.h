#ifndef LIST__H__
#define LIST__H__

struct list
{
   struct list* pred;
   struct list* succ;
   void* value;
};

struct list* List();

int empty(struct list* list);

struct list* head(struct list* list);

struct list* tail(struct list* list);

struct list* next(struct list* p);

struct list* prev(struct list* p);

int finished(struct list* list, struct list* p);

void* li_read(struct list* p);

void li_write(struct list* p, void* value);

struct list* li_insert(struct list* p, void* v);

struct list* li_remove(struct list* p);

#endif
