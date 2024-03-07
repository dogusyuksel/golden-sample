#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hwio.h"
#include "readperiodic.h"

#define OK 0
#define NOK 1

#define WAIT_IN_EACH_ITERATION 5

int main(int argc, char **args) {
    char *ptr = NULL;
    unsigned int timeout = 0;
    struct pin_identifier pidentifier;

    if (argc != 2) {
        printf("please provide one 'timeout' parameter\n");
        return NOK;
    }

    timeout = (unsigned int)strtoul(args[1], &ptr, 10);

    if (ptr && strlen(ptr) > 0) {
        return NOK;
    }

    pidentifier.port_name = PORT_B;
    pidentifier.pin_name = PIN_0;
    if (read_analog_periodicly(timeout, &pidentifier) != PERIODIC_OK) {
        printf("read_analog_periodicly() failed\n");
        return NOK;
    }
    printf("\n");
    pidentifier.port_name = PORT_A;
    pidentifier.pin_name = PIN_1;
    if (read_digital_periodicly(timeout, &pidentifier) != PERIODIC_OK) {
        printf("read_digital_periodicly() failed\n");
        return NOK;
    }
    printf("\n");

    return OK;
}
