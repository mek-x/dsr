#include <stdint.h>
#include <string.h>

#include "dsr.h"

uint8_t msg_buffer[100];
uint8_t msg_buffer_len;
uint8_t target_addr;

int DSR_send(uint8_t addr, const uint8_t * buf, uint8_t buf_len)
{
    memcpy(msg_buffer, buf, buf_len);
    msg_buffer_len = buf_len;
    target_addr = addr;

    return 5;
}

int DSR_getRouteCount(void)
{
    return 0;
}

const uint8_t * getMsg(void)
{
    return msg_buffer;
}

int getMsgLen(void)
{
    return msg_buffer_len;
}

uint8_t getMsgTarget(void)
{
    return target_addr;
}