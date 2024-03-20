#include <stdio.h>

#include "mylibrary.h"

bool mylib_echo(const char *str) {
    if (!str) {
        return false;
    }

    printf("%s :: %s\n", __func__, str);

    return true;
}
