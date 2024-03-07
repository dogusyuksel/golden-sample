#ifndef __READ_PERIODIC
#define __READ_PERIODIC

#include "hwio.h"

#define PERIODIC_OK 0
#define PERIODIC_NOK 1

int read_analog_periodicly(unsigned int timeout, struct pin_identifier *pidentifier);
int read_digital_periodicly(unsigned int timeout, struct pin_identifier *pidentifier);

#endif //__READ_PERIODIC
