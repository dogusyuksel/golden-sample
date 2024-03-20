#ifdef TEST

#include "unity.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "customprintrandom.h" //in src
#include "customprint.h" //in thirdparty

#include "mock_randombytegenerator.h" //in hwdependentcode


void setUp(void)
{
}

void tearDown(void)
{
}

void test_random_print_nok(void)
{
    bool rc = 0;

    rc = random_print(NULL);

    TEST_ASSERT_EQUAL(false, rc);
}

void test_random_print_ok(void)
{
    bool rc = 0;

    get_random_byte_ExpectAndReturn(true);

    rc = random_print(__func__);

    TEST_ASSERT_EQUAL(true, rc);
}

#endif // TEST
