#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tmr.h"

static struct tmr glb_timer_list[MAX_TIMER_CNT];
static unsigned char glb_total_timer_cnt = 0;

unsigned int tmr_create(void) {
    unsigned char i = 0;

    if (glb_total_timer_cnt >= MAX_TIMER_CNT) {
        return TMR_ERROR;
    }

    for (i = 0; i < MAX_TIMER_CNT; i++) {
        if (!glb_timer_list[i].is_initialized) {
            glb_timer_list[i].timer_id = i;
            glb_timer_list[i].ending_time = true;
            glb_timer_list[i].is_initialized = true;
            return i;
        }
    }

    return TMR_ERROR;
}

unsigned int tmr_start(unsigned char timer_id, unsigned long timeout) {
    struct timespec ts;

    if (timer_id >= MAX_TIMER_CNT) {
        return TMR_ERROR;
    }

    if (!glb_timer_list[timer_id].is_initialized) {
        return TMR_ERROR;
    }

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        return TMR_ERROR;
    }

    glb_timer_list[timer_id].ending_time = (long int)ts.tv_sec + (long int)timeout;

    return TMR_OK;
}

unsigned int tmr_delete(unsigned char timer_id) {
    if (timer_id >= MAX_TIMER_CNT) {
        return TMR_ERROR;
    }

    glb_timer_list[timer_id].timer_id = 0;
    glb_timer_list[timer_id].ending_time = 0;
    glb_timer_list[timer_id].is_initialized = false;

    return TMR_OK;
}

bool is_timeout(unsigned char timer_id) {
    struct timespec ts;

    if (timer_id >= MAX_TIMER_CNT) {
        return false;
    }

    if (!glb_timer_list[timer_id].is_initialized) {
        return false;
    }

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        return false;
    }

    if (ts.tv_sec >= glb_timer_list[timer_id].ending_time) {
        glb_timer_list[timer_id].timer_id = 0;
        glb_timer_list[timer_id].ending_time = 0;
        glb_timer_list[timer_id].is_initialized = false;
        return true;
    }

    return false;
}
