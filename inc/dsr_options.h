#ifndef DSR_OPTIONS_H
#define DSR_OPTIONS_H

#include <stdint.h>

int createRREQMsg(uint8_t *buf, uint8_t length, uint8_t target, uint8_t id);
int createRREPMsg(uint8_t *buf, uint8_t length, uint8_t *addr_list, uint8_t addr_list_len);

#endif /* DSR_OPTIONS_H */
