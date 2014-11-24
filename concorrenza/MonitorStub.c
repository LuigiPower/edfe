#include "MonitorStub.h"

void entry_mon(Monitor* monitor)
{
   P(&monitor->e);
}

void exit_mon(Monitor* monitor)
{
   V(&monitor->e);
}

void wait_mon(Monitor* monitor, Condition* cond)
{
   cond->n++;
   V(&monitor->e);
   P(&cond->c);
   P(&monitor->e);
}

void signal_mon(Monitor* monitor, Condition* cond)
{
   if(cond->n > 0)
   {
      cond->n--;
      V(&cond->c);
   }
}
