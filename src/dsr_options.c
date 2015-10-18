#include "dsr_options.h"

enum dsr_types_t {
    RERR_TYPE = 1,
    RREQ_TYPE,
    RREP_TYPE,
    AREQ_TYPE,
    AREP_TYPE,
    ROUTE_TYPE,
    DATA_TYPE
};

int createRREQMsg(uint8_t *buf, uint8_t length, uint8_t target, uint8_t id)
{
    uint8_t i = 0;

    if(length < 4)
        return -1;

    *buf++ = RREQ_TYPE;
    i++;

    *buf++ = 2;
    i++;

    *buf++ = id;
    i++;

    *buf++ = target;
    i++;

    return i;
}

int createRREPMsg(uint8_t *buf, uint8_t length, uint8_t *addr_list, uint8_t addr_list_len)
{
    uint8_t i = 0;

    if(length < addr_list_len + 2)
        return -1;

    *buf++ = RREP_TYPE;
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

int createRERRMsg(uint8_t *buf, uint8_t length, uint8_t err_type, uint8_t source, uint8_t target)
{
    uint8_t i = 0;

    if(length < 5)
        return -1;

    *buf++ = RERR_TYPE;
    i++;

    *buf++ = 3;
    i++;

    *buf++ = err_type;
    i++;

    *buf++ = source;
    i++;

    *buf++ = target;
    i++;

    return i;
}
