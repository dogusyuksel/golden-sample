#ifdef TEST

#include "unity.h"
#include <stdlib.h>
#include <string.h>

#include "readperiodic.h"
#include "tmr.h"

#include "mock_hwio.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_read_analog_periodicly_nok(void)
{
    int rc = 0;
    static struct pin_identifier pidentifier;

    pidentifier.port_name = PORT_A;
    pidentifier.pin_name = PIN_COUNT; //nok because of this line
    pidentifier.pin_type = ANALOG_IN;

    init_pin_ExpectAndReturn(&pidentifier, false);

    rc = read_analog_periodicly(1, &pidentifier);

    TEST_ASSERT_EQUAL(PERIODIC_NOK, rc);
}

void test_read_analog_periodicly_ok(void)
{
    int rc = 0;
    static struct pin_identifier pidentifier;

    pidentifier.port_name = PORT_A;
    pidentifier.pin_name = PIN_4;
    pidentifier.pin_type = ANALOG_IN;

    init_pin_ExpectAndReturn(&pidentifier, true);
    read_pin_ExpectAndReturn(&pidentifier, HWIO_OK);

    rc = read_analog_periodicly(1, &pidentifier);

    TEST_ASSERT_EQUAL(PERIODIC_OK, rc);
}

void test_read_digital_periodicly_nok(void)
{
    int rc = 0;
    static struct pin_identifier pidentifier;

    pidentifier.port_name = PORT_A;
    pidentifier.pin_name = PIN_1;
    pidentifier.pin_type = DIGITAL_IN;

    init_pin_ExpectAndReturn(&pidentifier, true);

    pidentifier.pin_name = PIN_COUNT; //nok because of this line
    read_pin_ExpectAndReturn(&pidentifier, HWIO_ERROR);

    rc = read_digital_periodicly(1, &pidentifier);

    TEST_ASSERT_EQUAL(PERIODIC_NOK, rc);
}

void test_read_digital_periodicly_ok(void)
{
    int rc = 0;
    static struct pin_identifier pidentifier;

    pidentifier.port_name = PORT_A;
    pidentifier.pin_name = PIN_5;
    pidentifier.pin_type = DIGITAL_IN;

    init_pin_ExpectAndReturn(&pidentifier, true);
    read_pin_ExpectAndReturn(&pidentifier, HWIO_OK);

    rc = read_digital_periodicly(1, &pidentifier);

    TEST_ASSERT_EQUAL(PERIODIC_OK, rc);
}

#endif // TEST
