#ifndef __BRIDGE_H__
#define __BRIDGE_H__
#include "MonitorStub.h"

#define NORD 0
#define SUD 1

Condition coda;
int in_coda;
int nauto;
int dircor;

void init();

void entra(Monitor* m, int d);

void esci(Monitor* m, int d);
#endif
