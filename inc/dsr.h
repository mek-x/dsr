#ifndef DSR_H
#define DSR_H


int DSR_send(uint8_t addr, const uint8_t *buf, uint8_t buf_len);
int DSR_receive(uint8_t *addr, uint8_t *buf, uint8_t buf_len);
int DSR_getRouteCount(void);
void DSR_init(void);
void DSR_destroy(void);

/* test functions */
const uint8_t * getMsg(void);
int getMsgLen(void);
uint8_t getMsgTarget(void);
void setRcvMsg(uint8_t addr, uint8_t *buf, uint8_t buf_len);

#endif /* DSR_H */
