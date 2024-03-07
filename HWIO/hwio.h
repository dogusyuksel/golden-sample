#ifndef __HWIO_H
#define __HWIO_H

#include <stdbool.h>

#define HWIO_ERROR -1
#define HWIO_OK 0

#pragma pack(1)
enum port_names { PORT_A, PORT_B, PORT_C, PORT_D, PORT_COUNT };

#pragma pack(1)
enum pin_names { PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_COUNT };

enum pin_type { ANALOG_IN, ANALOG_OUT, DIGITAL_IN, DIGITAL_OUT, UNDEFINED };

#pragma pack(1)
struct pin_identifier {
    enum port_names port_name;
    enum pin_names pin_name;
    enum pin_type pin_type;
    unsigned char data;
};

bool init_pin(struct pin_identifier *pidentifier);
int read_pin(struct pin_identifier *pidentifier);

#endif //__HWIO_H
