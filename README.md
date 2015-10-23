Dynamic Source Routing protocol implementation
==============================================

This is experimental implementation of DSR for simple wireless networks. Created
with nRF24L01 and RFM12 radio modules and simple uC's in mind.

Dynamic source routing protocol is used as a network layer in mesh-type
networks architecture. This particular implementation is loosely based on
following document for IPv4 networks:
* [Implementation for IPv4 networks (RFC 4728)](https://tools.ietf.org/html/rfc4728)

### DSR protocol
WIP

### DSR options
This implementation defines 7 types of DSR headers (options):

1. [Route error (RERR)](#route-error)
2. [Route request (RREQ)](#route-request)
3. [Route reply (RREP)](#route-reply)
4. [Acknowledge request (AREQ)](#acknowledge-request)
5. [Acknowledge reply (AREP)](#acknowledge-reply)
6. [Route (ROUT)](#route)
7. [Data (DATA)](#data)

In general each option has this form of header:
```
+------+--------+-----------------------------------------+
| TYPE | LENGTH | {option dependent variable length part} |
|  1   |   1    |                  1 - N                  |
+------+--------+-----------------------------------------+
```

Several options can create single packet. They are concatenated.

Requirements for lower level layers:
* Source and target addresses
* Length of whole payload

#### Route error
```
+------+--------+----------+--------+--------+
| TYPE | LENGTH | ERR_TYPE | SOURCE | TARGET |
|  1   |   1    |    1     |   1    |   1    |
+------+--------+----------+--------+--------+
```
* TYPE = 0x01
* May appear more than once in single packet

#### Route request
```
+------+--------+--------------------------------+
| TYPE | LENGTH |   ID   | TARGET | ADDRESS_LIST |
|  1   |   1    |   1    |   1    |    0 - N     |
+------+--------+--------------------------------+
```
* TYPE = 0x02
* May appear only once in single packet
* ADDRESS_LIST - on requester node this field is empty. It's getting filled
    by every node this option travels through.

#### Route reply
```
+------+--------+--------------+
| TYPE | LENGTH | ADDRESS_LIST |
|  1   |   1    |    1 - N     |
+------+--------+--------------+
```
* TYPE = 0x03
* May appear more than once in single packet

#### Acknowledge request
```
+------+--------+--------+
| TYPE | LENGTH |   ID   |
|  1   |   1    |   1    |
+------+--------+--------+
```
* TYPE = 0x04
* May appear only once in single packet

#### Acknowledge reply
```
+------+--------+--------+------------+------------+
| TYPE | LENGTH |   ID   | ACK_SOURCE | ACK_TARGET |
|  1   |   1    |   1    |     1      |     1      |
+------+--------+--------+------------+------------+
```
* TYPE = 0x05
* May appear more than once in single packet

#### Route
```
+------+--------+-----------+--------------+
| TYPE | LENGTH | SEGS_LEFT | ADDRESS_LIST |
|  1   |   1    |     1     |    1 - N     |
+------+--------+-----------+--------------+
```
* TYPE = 0x06
* May appear only once in single packet

#### Data
```
+------+--------+--------+
| TYPE | LENGTH |  DATA  |
|  1   |   1    | 1 - N  |
+------+--------+--------+
```
* TYPE = 0x07
* May appear only once in single packet
