#include "hwio.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool init_pin(struct pin_identifier *pidentifier) {
    if (!pidentifier) {
        return false;
    }

    if (pidentifier->port_name >= PORT_COUNT) {
        return false;
    }

    if (pidentifier->pin_name >= PIN_COUNT) {
        return false;
    }

    if (pidentifier->pin_type >= UNDEFINED) {
        return false;
    }

    return true;
}

int read_pin(struct pin_identifier *pidentifier) {
    struct timespec ts;
    unsigned char value = 0;

    if (!pidentifier) {
        return false;
    }

    if (pidentifier->port_name >= PORT_COUNT) {
        return false;
    }

    if (pidentifier->pin_name >= PIN_COUNT) {
        return false;
    }

    if (pidentifier->pin_type == ANALOG_OUT || pidentifier->pin_type == DIGITAL_OUT) {
        return HWIO_ERROR;
    }

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        return HWIO_ERROR;
    }
    srand((unsigned int)ts.tv_nsec);

    if (pidentifier->pin_type == DIGITAL_IN) {
        value = (unsigned char)(rand() % 2);
    }

    if (pidentifier->pin_type == ANALOG_IN) {
        value = (unsigned char)(rand() % 0xFF);
    }

    pidentifier->data = value;

    return HWIO_OK;
}
