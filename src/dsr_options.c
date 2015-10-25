#include "dsr_options.h"
#include <stdlib.h>

#define FIXED_HDR_LEN   2

#define RREQ_HDR_LEN    2
#define RREP_HDR_LEN    0
#define RERR_HDR_LEN    3
#define AREQ_HDR_LEN    1
#define AREP_HDR_LEN    3
#define ROUT_HDR_LEN    1
#define DATA_HDR_LEN    0

#define RERR_HDR(x) ((struct rerr_option *)(x))
#define RREQ_HDR(x) ((struct rreq_option *)(x))
#define RREP_HDR(x) ((struct rrep_option *)(x))
#define AREQ_HDR(x) ((struct areq_option *)(x))
#define AREP_HDR(x) ((struct arep_option *)(x))
#define ROUT_HDR(x) ((struct rout_option *)(x))
#define DATA_HDR(x) ((struct data_option *)(x))

#define RERR_LEN(header) (FIXED_HDR_LEN + RERR_HDR_LEN)
#define RREQ_LEN(header) (FIXED_HDR_LEN + RREQ_HDR_LEN + RREQ_HDR(header)->addr_list_len)
#define RREP_LEN(header) (FIXED_HDR_LEN + RREP_HDR_LEN + RREP_HDR(header)->addr_list_len)
#define AREQ_LEN(header) (FIXED_HDR_LEN + AREQ_HDR_LEN)
#define AREP_LEN(header) (FIXED_HDR_LEN + AREP_HDR_LEN)
#define ROUT_LEN(header) (FIXED_HDR_LEN + ROUT_HDR_LEN + ROUT_HDR(header)->addr_list_len)
#define DATA_LEN(header) (FIXED_HDR_LEN + DATA_HDR_LEN + DATA_HDR(header)->data_len)

#define CHECK_LEN(type, length, header) \
    ((length) >= type ## _LEN(header) ? type ## _LEN(header) : ERROR_CREATE_MSG)

#define TYPE_HEADER_MASK 0x07

static uint8_t checkHeaderAndReturnLength(enum dsr_types_t type, uint8_t length, void *header);
static uint8_t checkHeaderAndReturnLength(enum dsr_types_t type, uint8_t length, void *header)
{
    switch (type) {
    case RERR_TYPE:
        length = CHECK_LEN(RERR, length, header);
        break;
    case RREQ_TYPE:
        length = CHECK_LEN(RREQ, length, header);
        if (RREQ_HDR(header)->addr_list == NULL && RREQ_HDR(header)->addr_list_len > 0)
            length = ERROR_CREATE_MSG;
        break;
    case RREP_TYPE:
        length = CHECK_LEN(RREP, length, header);
        if (RREP_HDR(header)->addr_list == NULL || RREP_HDR(header)->addr_list_len == 0)
            length = ERROR_CREATE_MSG;
        break;
    case AREQ_TYPE:
        length = CHECK_LEN(AREQ, length, header);
        break;
    case AREP_TYPE:
        length = CHECK_LEN(AREP, length, header);
        break;
    case ROUT_TYPE:
        length = CHECK_LEN(ROUT, length, header);
        if (ROUT_HDR(header)->addr_list == NULL || ROUT_HDR(header)->addr_list_len == 0)
            length = ERROR_CREATE_MSG;
        break;
    case DATA_TYPE:
        length = CHECK_LEN(DATA, length, header);
        if (DATA_HDR(header)->data == NULL || DATA_HDR(header)->data_len == 0)
            length = ERROR_CREATE_MSG;
        break;
    default:
        length = ERROR_CREATE_MSG;
        break;
    }
    return length;
}

static int createMsg(enum dsr_types_t type, uint8_t *buf, uint8_t length, void *header);
static int createMsg(enum dsr_types_t type, uint8_t *buf, uint8_t length, void *header)
{
    if (NULL == buf || NULL == header)
        return ERROR_CREATE_MSG;

    length = checkHeaderAndReturnLength(type, length, header);
    if (ERROR_CREATE_MSG == length)
        return ERROR_CREATE_MSG;

    *buf++ = type;
    *buf++ = length - FIXED_HDR_LEN;

    switch (type) {
    case RERR_TYPE:
        *buf++ = RERR_HDR(header)->err_type;
        *buf++ = RERR_HDR(header)->source;
        *buf++ = RERR_HDR(header)->target;
        break;

    case RREQ_TYPE:
        *buf++ = RREQ_HDR(header)->id;
        *buf++ = RREQ_HDR(header)->target;
        while(RREQ_HDR(header)->addr_list_len--)
            *buf++ = *(RREQ_HDR(header)->addr_list)++;
        break;

    case RREP_TYPE:
        while(RREP_HDR(header)->addr_list_len--)
            *buf++ = *(RREP_HDR(header)->addr_list)++;
        break;

    case AREQ_TYPE:
        *buf++ = AREQ_HDR(header)->id;
        break;

    case AREP_TYPE:
        *buf++ = AREP_HDR(header)->id;
        *buf++ = AREP_HDR(header)->source;
        *buf++ = AREP_HDR(header)->target;
        break;

    case ROUT_TYPE:
        *buf++ = ROUT_HDR(header)->segments_left;
        while(ROUT_HDR(header)->addr_list_len--)
            *buf++ = *(ROUT_HDR(header)->addr_list)++;
        break;

    case DATA_TYPE:
        while(DATA_HDR(header)->data_len--)
            *buf++ = *(DATA_HDR(header)->data)++;
        break;
    default:
        break;
    }

    return length;
}

inline int createRREQMsg(uint8_t *buf, uint8_t length, struct rreq_option header)
{
    return createMsg(RREQ_TYPE, buf, length, &header);
}

inline int createRREPMsg(uint8_t *buf, uint8_t length, struct rrep_option header)
{
    return createMsg(RREP_TYPE, buf, length, &header);
}

inline int createRERRMsg(uint8_t *buf, uint8_t length, struct rerr_option header)
{
    return createMsg(RERR_TYPE, buf, length, &header);
}

inline int createAREQMsg(uint8_t *buf, uint8_t length, struct areq_option header)
{
    return createMsg(AREQ_TYPE, buf, length, &header);
}

inline int createAREPMsg(uint8_t *buf, uint8_t length, struct arep_option header)
{
    return createMsg(AREP_TYPE, buf, length, &header);
}

inline int createROUTMsg(uint8_t *buf, uint8_t length, struct rout_option header)
{
    return createMsg(ROUT_TYPE, buf, length, &header);
}

inline int createDATAMsg(uint8_t *buf, uint8_t length, struct data_option header)
{
    return createMsg(DATA_TYPE, buf, length, &header);
}

enum dsr_types_t getMsgType(const uint8_t *buf)
{
    if (((*buf & (~TYPE_HEADER_MASK)) != 0) ||
        ((*buf & TYPE_HEADER_MASK) == 0))
        return TYPE_ERROR;

    return *buf;
}
