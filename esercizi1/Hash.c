#include "Hash.h"
#include <stdlib.h>
#include <stdio.h>

void delete(unsigned char* where, int size)
{
   for(int i = 0; i < size; i++)
   {
      *where = 255;
      where++;
   }
}

void write(unsigned char* where, unsigned char* what, int size)
{
   for(int i = 0; i < size; i++)
   {
      *where = *what;
      where++;
      what++;
   }
}

int is_null(unsigned char* key, int size)
{
   for(int i = 0; i < size; i++)
   {
      if(*key != 0)
      {
         return 0;
      }
      key++;
   }
   return 1;
}

int is_deleted(unsigned char* key, int size)
{
   for(int i = 0; i < size; i++)
   {
      if(*key != 255)
      {
         return 0;
      }
      key++;
   }
   return 1;
}

int equals(unsigned char* one, unsigned char* two, int size)
{
   for(int i = 0; i < size; i++)
   {
      if(*one != *two)
      {
         return 0;
      }
      one++;
      two++;
   }
   return 1;
}

struct hash_table* Hash(int capacity, int sizekeyel, int sizevalueel, int(*hash_func)(void*key))
{
   struct hash_table* t = (struct hash_table*) malloc(sizeof(struct hash_table));
   t->keys = (void*) malloc(sizekeyel * capacity);
   t->values = (void*) malloc(sizevalueel * capacity);
   t->n = capacity;
   t->sizekeyel = sizekeyel;
   t->sizevalueel = sizevalueel;
   t->hash_func = hash_func;
   return t;
}

int scan(struct hash_table* table, void* key, int insert)
{
   int c = table->n;
   int i = 0;
   int j = table->hash_func(key);

   int k_size = table->sizekeyel;
   void* a = table->keys + j * k_size;

   while(!equals(a, key, k_size) && !is_null(a, k_size) && i < table->n)
   {
      if(is_deleted(a, k_size) && c == table->n)
         c = j;
      j = (j + 1) % table->n;
      i++;

      a = table->keys + j * k_size;
   }
   if(insert && !equals(a, key, k_size) && c < table->n)
      j = c;
   return j;
}

int scan_custom(struct hash_table* table, void* key, int insert, int(*equals_custom)(void* one, void* two))
{
   int c = table->n;
   int i = 0;
   int j = table->hash_func(key);

   int k_size = table->sizekeyel;
   void* a = table->keys + j * k_size;

   while(!equals_custom(a, key) && !is_null(a, k_size) && i < table->n)
   {
      if(is_deleted(a, k_size) && c == table->n)
         c = j;
      j = (j + 1) % table->n;
      i++;

      a = table->keys + j * k_size;
   }
   if(insert && !equals_custom(a, key) && c < table->n)
      j = c;
   printf("Stopping for: %d %d %d\n", !equals_custom(a, key), !is_null(a, k_size), i < table->n);
   return j;
}


void* lookup_custom(struct hash_table* table, void* key, int(*equals_custom)(void* one, void* two))
{
   int i = scan_custom(table, key, 0, equals_custom);
   if(equals_custom(table->keys + i * table->sizekeyel, key))
   {
      return table->values + table->sizevalueel * i;
   }
   else
   {
      return NULL;
   }
}


void* lookup(struct hash_table* table, void* key)
{
   int i = scan(table, key, 0);
   if(equals(table->keys + i * table->sizekeyel, key, table->sizekeyel))
   {
      return table->values + table->sizevalueel * i;
   }
   else
   {
      return NULL;
   }
}

void insert(struct hash_table* table, void* key, void* value)
{
   int i = scan(table, key, 1);
   void* pointed = table->keys + i * table->sizekeyel;
   int result = is_null(pointed, table->sizekeyel) || is_deleted(pointed, table->sizekeyel) || equals(pointed, key, table->sizekeyel);
   if(result)
   {
      write(pointed, key, table->sizekeyel);
      write(table->values + i * table->sizevalueel, value, table->sizevalueel);
   }
   else
   {
      fprintf(stderr, "ERROR: HashTable full\n");
   }
}

void remove_el(struct hash_table* table, void* key)
{
   int i = scan(table, key, 0);
   void* a = table->keys + i * table->sizekeyel;
   if(equals(a, key, table->sizekeyel))
   {
      delete(a, table->sizekeyel);
   }
}

