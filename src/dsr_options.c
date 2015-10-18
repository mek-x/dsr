#include "dsr_options.h"

int createRREQMsg(uint8_t *buf, uint8_t length, uint8_t target, uint8_t id)
{
    uint8_t i = 0;

    if(length < 4)
        return -1;

    *buf++ = 0x20;
    i++;

    *buf++ = 0x02;
    i++;

    *buf++ = id;
    i++;

    *buf++ = target;
    i++;

    return i;
}
