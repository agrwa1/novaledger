#ifndef TYPES_NET_H
#define TYPES_NET_H

#include <vector>

enum msg_type {
    // INIT & INFRA
    VERSION = 0x01,
    VERACK = 0x02,
    REQPEERS = 0x03,
    SENDPEERS = 0x04,
    PING = 0x05,
    PONG = 0x06,
    EXIT = 0x07,

    // TX PROPAGATION
    PROPTX = 0x08,
    REQTX = 0x09,
    SENDTX = 0x0A,
    REQMEM = 0x0B,
    SENDMEM = 0x0C,

    // BLK PROPAGATION
    PROPBLK = 0x0D,
    REQBLK = 0x0E,
    SENDBLK = 0x0F,
    SENDBLKHEAD = 0x10,
    REQBLKCHN = 0x11
};

// requires body to be pre-serialized and then serialize entire message
struct net_msg {
    // HEADER
    uint8_t protocol_version;
    uint8_t type;
    uint32_t length;

    // PAYLOAD
    std::vector<uint8_t> payload;
};

#endif