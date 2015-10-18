#ifndef DSR_OPTIONS_H
#define DSR_OPTIONS_H

#include <stdint.h>

int createRREQMsg(uint8_t *buf, uint8_t length, uint8_t target, uint8_t id);
int createRREPMsg(uint8_t *buf, uint8_t length, uint8_t *addr_list, uint8_t addr_list_len);
int createRERRMsg(uint8_t *buf, uint8_t length, uint8_t err_type, uint8_t source, uint8_t target);

#endif /* DSR_OPTIONS_H */
