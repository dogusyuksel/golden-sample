#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hwio.h"
#include "readperiodic.h"
#include "tmr.h"

static int read_pin_periodic(unsigned int timeout, struct pin_identifier *pidentifier) {
    unsigned int timer = 0;

    if (!timeout || !pidentifier) {
        return PERIODIC_NOK;
    }

    if (init_pin(pidentifier) != true) {
        return PERIODIC_NOK;
    }

    timer = tmr_create();
    if (timer == TMR_ERROR) {
        return PERIODIC_NOK;
    }
    if (tmr_start(timer, timeout) == TMR_ERROR) {
        return PERIODIC_NOK;
    }
    while (!is_timeout(timer)) {
        sleep(1);
    }
    if (tmr_delete(timer) == TMR_ERROR) {
        return PERIODIC_NOK;
    }
    if (read_pin(pidentifier) == HWIO_ERROR) {
        return PERIODIC_NOK;
    }
    printf(" 0x%02X", (unsigned int)pidentifier->data);

    return PERIODIC_OK;
}

int read_analog_periodicly(unsigned int timeout, struct pin_identifier *pidentifier) {
    printf("%s ->\t\t", __func__);
    pidentifier->pin_type = ANALOG_IN;
    return read_pin_periodic(timeout, pidentifier);
}

int read_digital_periodicly(unsigned int timeout, struct pin_identifier *pidentifier) {
    printf("%s ->\t\t", __func__);
    pidentifier->pin_type = DIGITAL_IN;
    return read_pin_periodic(timeout, pidentifier);
}
