#include <stdint.h>
#include <string.h>

#include "dsr.h"

struct msg_t {
    uint8_t buffer[100];
    uint8_t length;
    uint8_t target;
} msg;

void DSR_init(void)
{
    memset(&msg, 0, sizeof(msg));
}

void DSR_destroy(void)
{
}

int DSR_send(uint8_t addr, const uint8_t *buf, uint8_t buf_len)
{
    msg.length = buf_len;
    memcpy(msg.buffer, buf, msg.length);
    msg.target = addr;

    return 5;
}

int DSR_receive(uint8_t *addr, uint8_t *buf, uint8_t buf_len)
{
    *addr = msg.target;
    memcpy(buf, msg.buffer, buf_len);

    return msg.length;
}

int DSR_getRouteCount(void)
{
    return 0;
}

const uint8_t * getMsg(void)
{
    return msg.buffer;
}

int getMsgLen(void)
{
    return msg.length;
}

uint8_t getMsgTarget(void)
{
    return msg.target;
}

void setRcvMsg(uint8_t addr, uint8_t *buf, uint8_t buf_len)
{
    msg.target = addr;
    memcpy(msg.buffer, buf, buf_len);
    msg.length = buf_len;
}
