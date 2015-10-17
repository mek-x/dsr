#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dsr.h"

struct msg_t {
    uint8_t buffer[MSG_MAX_LEN];
    uint8_t length;
    uint8_t target;
};

static struct msg_t recv_msg;

struct dsr_t {
    uint8_t node_addr;
    int queue_index;
    struct msg_t msg_queue[MSG_BUFFER_SIZE];
};

/* private prototypes */
int queue_message(DSR_Node node, uint8_t addr, uint8_t *buf, uint8_t length);

/* public interface */
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
    queue_message(node, addr, buf, length);

    return length;
}

int DSR_receive(DSR_Node node, uint8_t *addr, uint8_t *buf, uint8_t length)
{
    (void)node;

    *addr = recv_msg.target;
    memcpy(buf, recv_msg.buffer, length);

    return recv_msg.length;
}

int DSR_getRouteCount(DSR_Node node)
{
    (void)node;

    return 0;
}

/* private functions implementation */
int queue_message(DSR_Node node, uint8_t addr, uint8_t *buf, uint8_t length)
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

void setRcvMsg(uint8_t addr, uint8_t *buf, uint8_t buf_len)
{

    recv_msg.target = addr;
    memcpy(recv_msg.buffer, buf, buf_len);
    recv_msg.length = buf_len;
}
