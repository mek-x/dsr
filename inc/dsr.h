#ifndef DSR_H
#define DSR_H

uint8_t DSR_msg_buffer[100];
uint8_t DSR_msg_buffer_len;

int DSR_send(uint8_t addr, const uint8_t * buf, uint8_t buf_len);
int DSR_getRouteCount(void);

#endif /* DSR_H */
