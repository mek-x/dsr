#include "dsr_options.h"

int createRREQMsg(uint8_t *buf, uint8_t length, uint8_t target)
{
    (void)length;
    (void)target;

    uint8_t i = 0;

    *buf++ = 0x20;
    i++;

    *buf++ = 0x02;
    i++;

    *buf++ = 0x00;
    i++;

    *buf++ = target;
    i++;

    return i;
}
