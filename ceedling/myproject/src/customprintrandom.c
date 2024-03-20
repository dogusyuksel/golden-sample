#include <stdio.h>

#include "customprint.h"
#include "customprintrandom.h"
#include "randombytegenerator.h"

bool random_print(const char *str) {
    char buffer[32];

    if (!str) {
        return false;
    }

    memset(buffer, 0, sizeof(buffer));

    snprintf(buffer, 32, "%u-%s", (unsigned int)get_random_byte(), str);
    return custom_print((const char *)buffer);
}
