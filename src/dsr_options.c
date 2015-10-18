#include "dsr_options.h"

enum dsr_types_t {
    RERR_TYPE = 1,
    RREQ_TYPE,
    RREP_TYPE,
    AREQ_TYPE,
    AREP_TYPE,
    ROUT_TYPE,
    DATA_TYPE
};

#define RREQ_HDR_LEN 4
#define RREP_HDR_LEN 2
#define RERR_LEN 5
#define AREQ_LEN 3
#define AREP_LEN 5
#define ROUT_HDR_LEN 3

int createRREQMsg(uint8_t *buf, uint8_t length, uint8_t id, uint8_t target)
{
    if(length < RREQ_HDR_LEN)
        return -1;

    *buf++ = RREQ_TYPE;
    *buf++ = 2;
    *buf++ = id;
    *buf++ = target;

    return RREQ_HDR_LEN;
}

int createRREPMsg(uint8_t *buf, uint8_t length, uint8_t *addr_list, uint8_t addr_list_len)
{
    if(length < RREP_HDR_LEN + addr_list_len)
        return -1;

    length = RREP_HDR_LEN + addr_list_len;

    *buf++ = RREP_TYPE;
    *buf++ = addr_list_len;

    while(addr_list_len--)
        *buf++ = *addr_list++;

    return length;
}

int createRERRMsg(uint8_t *buf, uint8_t length, uint8_t err_type, uint8_t source, uint8_t target)
{
    if(length < RERR_LEN)
        return -1;

    *buf++ = RERR_TYPE;
    *buf++ = 3;
    *buf++ = err_type;
    *buf++ = source;
    *buf++ = target;

    return RERR_LEN;
}

int createAREQMsg(uint8_t *buf, uint8_t length, uint8_t id)
{
    if(length < AREQ_LEN)
        return -1;

    *buf++ = AREQ_TYPE;
    *buf++ = 1;
    *buf++ = id;

    return AREQ_LEN;
}

int createAREPMsg(uint8_t *buf, uint8_t length, uint8_t id, uint8_t ack_source, uint8_t ack_target)
{
    if(length < AREP_LEN)
        return -1;

    *buf++ = AREP_TYPE;
    *buf++ = 3;
    *buf++ = id;
    *buf++ = ack_source;
    *buf++ = ack_target;

    return AREP_LEN;
}

int createROUTMsg(uint8_t *buf, uint8_t length, uint8_t *addr_list, uint8_t addr_list_len)
{
    if(length < ROUT_HDR_LEN + addr_list_len)
        return -1;

    length = ROUT_HDR_LEN + addr_list_len;

    *buf++ = ROUT_TYPE;
    *buf++ = addr_list_len + 1;
    *buf++ = addr_list_len; // segments left

    while(addr_list_len--)
        *buf++ = *addr_list++;

    return length;
}
