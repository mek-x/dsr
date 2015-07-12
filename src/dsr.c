#include <stdint.h>
#include <string.h>

#include "dsr.h"

int DSR_send(uint8_t addr, const uint8_t * buf, uint8_t buf_len)
{
    (void)addr;
    (void)buf;
    (void)buf_len;

    memcpy(DSR_msg_buffer, buf, buf_len);
    DSR_msg_buffer_len = buf_len;

    return 5;
}

int DSR_getRouteCount(void)
{
    return 0;
}