#ifndef PRIORITYQUEUE__H__
#define PRIORITYQUEUE__H__

struct priority_item
{
   int priority;
   void* value;
   int pos;
};

struct priority_queue
{
   int capacity;
   int dim;
   struct priority_item* h;
};

int is_empty(struct priority_queue*);

struct priority_queue* PriorityQueue(int n);

void* min(struct priority_queue* queue);

struct priority_item* pq_insert(struct priority_queue* queue, void* x, int p);

struct priority_item* pq_item_insert(struct priority_queue* queue, struct priority_item* item);

void swap_pri(struct priority_item* h, int i, int j);

int compare(void* one, void* two);

struct priority_item deleteMin(struct priority_queue* queue);

void decrease(struct priority_queue* queue, struct priority_item* x, int p);

int contains(struct priority_queue* queue, struct priority_item* item, int size);

#endif
