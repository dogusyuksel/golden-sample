#include <stdlib.h>

#include "customprintrandom.h"

int main(void) {
    if (random_print((const char *)"hello world\n") == false) {
        exit(1);
    }

    exit(0);
}
