#include <stdio.h>

#include "customprint.h"

bool custom_print(const char *str) {
    if (!str) {
        return false;
    }

    printf("%s :: %s", __func__, str);

    return true;
}
