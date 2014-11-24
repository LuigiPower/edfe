#ifndef __MONITOR_H__
#define __MONITOR_H__
#include "Semaphore.h"

typedef struct monitor
{
   Semaphore e;
} Monitor;

typedef struct condition
{
   int n;
   Semaphore c;
} Condition;

void entry_mon(Monitor* monitor);
void exit_mon(Monitor* monitor);

void wait_mon(Monitor* monitor, Condition* cond);
void signal_mon(Monitor* monitor, Condition* cond);
#endif
