#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "randombytegenerator.h"

unsigned char get_random_byte(void) {
    struct timespec ts;

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        return 0;
    }
    srand((unsigned int)ts.tv_nsec);

    return ((unsigned char)(rand() % 0xFF));
}
