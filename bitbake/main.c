#include <stdio.h>

int main(void) {
#ifdef DEBUG_ENABLED
    printf("hello bitbake with debug\n");
#else
    printf("hello bitbake\n");
#endif
}
