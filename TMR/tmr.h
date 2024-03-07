#ifndef __TMR_H
#define __TMR_H

#include <stdbool.h>

#define MAX_TIMER_CNT 0xFF

#define TMR_ERROR MAX_TIMER_CNT + 1
#define TMR_OK 0

struct tmr {
    unsigned char timer_id;
    long int ending_time;
    bool is_initialized;
};

unsigned int tmr_create(void);
unsigned int tmr_start(unsigned char timer_id, unsigned long timeout);
unsigned int tmr_delete(unsigned char timer_id);
bool is_timeout(unsigned char timer_id);

#endif //__TMR_H
