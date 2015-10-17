#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dsr.h"

struct msg_t {
    uint8_t buffer[MSG_MAX_LEN];
    uint8_t length;
    uint8_t target;
};

struct dsr_t {
    uint8_t address;
    int queue_index;
    struct msg_t msg_queue[MSG_BUFFER_SIZE];
    struct msg_t recv_msg;
};

/* private prototypes */
static int queue_message(DSR_Node node, uint8_t addr, uint8_t *buf, uint8_t length);

/* public interface */
DSR_Node DSR_init(uint8_t node_addr)
{
    DSR_Node node;

    node = calloc(1, sizeof(struct dsr_t));
    node->address = node_addr;

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
    if (queue_message(node, addr, buf, length) != 0)
        return -1;

    return length;
}

int DSR_receive(DSR_Node node, uint8_t *addr, uint8_t *buf, uint8_t length)
{
    *addr = node->recv_msg.target;
    memcpy(buf, node->recv_msg.buffer, length);

    return node->recv_msg.length;
}

int DSR_getRouteCount(DSR_Node node)
{
    (void)node;

    return 0;
}

/* private functions implementation */
static int queue_message(DSR_Node node, uint8_t addr, uint8_t *buf, uint8_t length)
{
    if (node->queue_index >= MSG_BUFFER_SIZE) {
        return -1;
    }
    node->msg_queue[node->queue_index].length = length;
    node->msg_queue[node->queue_index].target = addr;
    memcpy(node->msg_queue[node->queue_index].buffer,
           buf,
           node->msg_queue[node->queue_index].length);
    node->queue_index++;

    return 0;
}


/* testing functions */
const uint8_t * getMsg(DSR_Node node, int index)
{
    return node->msg_queue[index].buffer;
}

int getMsgLen(DSR_Node node, int index)
{
    return node->msg_queue[index].length;
}

uint8_t getMsgTarget(DSR_Node node, int index)
{
    return node->msg_queue[index].target;
}

void setRcvMsg(DSR_Node node, uint8_t addr, uint8_t *buf, uint8_t buf_len)
{
    node->recv_msg.target = addr;
    memcpy(node->recv_msg.buffer, buf, buf_len);
    node->recv_msg.length = buf_len;
}

uint8_t getNodeAddr(DSR_Node node)
{
    return node->address;
}
