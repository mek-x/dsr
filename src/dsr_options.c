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

int createRREPMsg(uint8_t *buf, uint8_t length, uint8_t *addr_list, uint8_t addr_list_len)
{
    (void)length;
    uint8_t i = 0;

    *buf++ = 0x30;
    i++;

    *buf++ = addr_list_len;
    i++;

    while(addr_list_len--)
    {
        *buf++ = *addr_list++;
        i++;
    }

    return i;
}
