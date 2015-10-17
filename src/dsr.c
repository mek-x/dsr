#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dsr.h"

struct msg_t {
    uint8_t buffer[100];
    uint8_t length;
    uint8_t target;
} msg;

struct dsr_t {
    uint8_t node_addr;
};

DSR_Node DSR_init(uint8_t node_addr)
{
    DSR_Node node;

    node = calloc(1, sizeof(struct dsr_t));
    node->node_addr = node_addr;

    return node;
}

void DSR_destroy(DSR_Node *node)
{
    if (*node != NULL)
        free(*node);

    *node = NULL;
}

int DSR_send(DSR_Node node, uint8_t addr, uint8_t *buf, uint8_t length)
{
    (void)node;

    msg.length = length;
    memcpy(msg.buffer, buf, msg.length);
    msg.target = addr;

    return 5;
}

int DSR_receive(DSR_Node node, uint8_t *addr, uint8_t *buf, uint8_t length)
{
    (void)node;

    *addr = msg.target;
    memcpy(buf, msg.buffer, length);

    return msg.length;
}

int DSR_getRouteCount(DSR_Node node)
{
    (void)node;

    return 0;
}


/* testing functions */
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
