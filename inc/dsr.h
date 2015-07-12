#ifndef DSR_H
#define DSR_H


int DSR_send(uint8_t addr, const uint8_t * buf, uint8_t buf_len);
int DSR_getRouteCount(void);


const uint8_t * getMsg(void);
int getMsgLen(void);
uint8_t getMsgTarget(void);

#endif /* DSR_H */
