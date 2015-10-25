#include "dsr_options.h"
#include <stdlib.h>

enum dsr_types_t {
    RERR_TYPE = 1,
    RREQ_TYPE,
    RREP_TYPE,
    AREQ_TYPE,
    AREP_TYPE,
    ROUT_TYPE,
    DATA_TYPE
};

#define CONSTANT_HDR_LEN    2
#define RREQ_HDR_LEN        2
#define RREP_HDR_LEN        0
#define RERR_HDR_LEN        3
#define AREQ_HDR_LEN        1
#define AREP_HDR_LEN        3
#define ROUT_HDR_LEN        1
#define DATA_HDR_LEN        0

int createRREQMsg(uint8_t *buf, uint8_t length, uint8_t id, uint8_t target, uint8_t *addr_list, uint8_t addr_list_len)
{
    if ((buf == NULL) ||
        (length < CONSTANT_HDR_LEN + RREQ_HDR_LEN + addr_list_len) ||
        (addr_list == NULL && addr_list_len != 0))
        return ERROR_CREATE_MSG;

    length = CONSTANT_HDR_LEN + RREQ_HDR_LEN + addr_list_len;

    *buf++ = RREQ_TYPE;
    *buf++ = RREQ_HDR_LEN + addr_list_len;
    *buf++ = id;
    *buf++ = target;

    while(addr_list_len--)
        *buf++ = *addr_list++;

    return length;
}

int createRREPMsg(uint8_t *buf, uint8_t length, uint8_t *addr_list, uint8_t addr_list_len)
{
    if ((buf == NULL || addr_list == NULL)  ||
        (length < CONSTANT_HDR_LEN + addr_list_len) ||
        (0 == addr_list_len))
        return ERROR_CREATE_MSG;

    length = CONSTANT_HDR_LEN + addr_list_len;

    *buf++ = RREP_TYPE;
    *buf++ = addr_list_len;

    while(addr_list_len--)
        *buf++ = *addr_list++;

    return length;
}

int createRERRMsg(uint8_t *buf, uint8_t length, uint8_t err_type, uint8_t source, uint8_t target)
{
    if ((buf == NULL) ||
        (length < CONSTANT_HDR_LEN + RERR_HDR_LEN))
        return ERROR_CREATE_MSG;

    *buf++ = RERR_TYPE;
    *buf++ = RERR_HDR_LEN;
    *buf++ = err_type;
    *buf++ = source;
    *buf++ = target;

    return CONSTANT_HDR_LEN + RERR_HDR_LEN;
}

int createAREQMsg(uint8_t *buf, uint8_t length, uint8_t id)
{
    if ((buf == NULL) ||
        (length < CONSTANT_HDR_LEN + AREQ_HDR_LEN))
        return ERROR_CREATE_MSG;

    *buf++ = AREQ_TYPE;
    *buf++ = AREQ_HDR_LEN;
    *buf++ = id;

    return CONSTANT_HDR_LEN + AREQ_HDR_LEN;
}

int createAREPMsg(uint8_t *buf, uint8_t length, uint8_t id, uint8_t ack_source, uint8_t ack_target)
{
    if ((buf == NULL) ||
        (length < CONSTANT_HDR_LEN + AREP_HDR_LEN))
        return ERROR_CREATE_MSG;

    *buf++ = AREP_TYPE;
    *buf++ = AREP_HDR_LEN;
    *buf++ = id;
    *buf++ = ack_source;
    *buf++ = ack_target;

    return CONSTANT_HDR_LEN + AREP_HDR_LEN;
}

int createROUTMsg(uint8_t *buf, uint8_t length, uint8_t *addr_list, uint8_t addr_list_len)
{
    if ((buf == NULL || addr_list == NULL) ||
        (length < CONSTANT_HDR_LEN + ROUT_HDR_LEN + addr_list_len) ||
        (0 == addr_list_len))
        return ERROR_CREATE_MSG;

    length = CONSTANT_HDR_LEN + ROUT_HDR_LEN + addr_list_len;

    *buf++ = ROUT_TYPE;
    *buf++ = addr_list_len + 1;
    *buf++ = addr_list_len; // segments left

    while(addr_list_len--)
        *buf++ = *addr_list++;

    return length;
}

int createDATAMsg(uint8_t *buf, uint8_t length, uint8_t *data, uint8_t data_len)
{
    if ((buf == NULL || data == NULL) ||
        (length < CONSTANT_HDR_LEN + data_len) ||
        (0 == data_len))
        return ERROR_CREATE_MSG;

    length = CONSTANT_HDR_LEN + data_len;

    *buf++ = DATA_TYPE;
    *buf++ = data_len;

    while(data_len--)
        *buf++ = *data++;

    return length;
}
