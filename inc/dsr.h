#ifndef DSR_H
#define DSR_H

typedef struct dsr_t *DSR_Node;

DSR_Node DSR_init(uint8_t node_address);
void DSR_destroy(DSR_Node *node);

int DSR_send(DSR_Node node, uint8_t addr, uint8_t *buf, uint8_t length);
int DSR_receive(DSR_Node node, uint8_t *addr, uint8_t *buf, uint8_t length);
int DSR_getRouteCount(DSR_Node node);

/* test functions */
const uint8_t * getMsg(void);
int getMsgLen(void);
uint8_t getMsgTarget(void);
void setRcvMsg(uint8_t addr, uint8_t *buf, uint8_t buf_len);

#endif /* DSR_H */
