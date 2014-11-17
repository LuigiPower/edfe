#ifndef HASH__H__
#define HASH__H__

struct hash_table
{
   int n;

   int sizekeyel;
   int sizevalueel;

   void* keys;
   void* values;

   int(*hash_func)(void* key);
};

struct hash_table* Hash(int capacity, int sizekeyel, int sizevalueel, int(*hash_func)(void* key));

int scan(struct hash_table* table, void* key, int insert);

int equals(unsigned char* one, unsigned char* two, int size);

void* lookup(struct hash_table* table, void* key);

void* lookup_custom(struct hash_table* table, void* key, int(*equals_custom)(void* one, void* two));

void remove_el(struct hash_table* table, void* key);

void insert(struct hash_table* table, void* key, void* value);

#endif
