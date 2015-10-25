#ifndef DSR_OPTIONS_H
#define DSR_OPTIONS_H

#include <stdint.h>

#define ERROR_CREATE_MSG 0

struct rreq_option {
    uint8_t id;
    uint8_t target;
    uint8_t *addr_list;
    uint8_t addr_list_len;
};

struct rrep_option {
    uint8_t *addr_list;
    uint8_t addr_list_len;
};

struct rerr_option {
    uint8_t err_type;
    uint8_t source;
    uint8_t target;
};

struct areq_option {
    uint8_t id;
};

struct arep_option {
    uint8_t id;
    uint8_t source;
    uint8_t target;
};

struct rout_option {
    uint8_t segments_left;
    uint8_t *addr_list;
    uint8_t addr_list_len;
};

struct data_option {
    uint8_t *data;
    uint8_t data_len;
};

int createRREQMsg(uint8_t *buf, uint8_t length, struct rreq_option header);
int createRREPMsg(uint8_t *buf, uint8_t length, struct rrep_option header);
int createRERRMsg(uint8_t *buf, uint8_t length, struct rerr_option header);
int createAREQMsg(uint8_t *buf, uint8_t length, struct areq_option header);
int createAREPMsg(uint8_t *buf, uint8_t length, struct arep_option header);
int createROUTMsg(uint8_t *buf, uint8_t length, struct rout_option header);
int createDATAMsg(uint8_t *buf, uint8_t length, struct data_option header);

uint8_t *getRREQMsg(const uint8_t *buf, uint8_t length, struct rreq_option *header);
uint8_t *getRREPMsg(const uint8_t *buf, uint8_t length, struct rreq_option *header);
uint8_t *getRERRMsg(const uint8_t *buf, uint8_t length, struct rreq_option *header);
uint8_t *getAREQMsg(const uint8_t *buf, uint8_t length, struct rreq_option *header);
uint8_t *getAREPMsg(const uint8_t *buf, uint8_t length, struct rreq_option *header);
uint8_t *getROUTMsg(const uint8_t *buf, uint8_t length, struct rreq_option *header);
uint8_t *getDATAMsg(const uint8_t *buf, uint8_t length, struct rreq_option *header);

#endif /* DSR_OPTIONS_H */
