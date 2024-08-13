#include <iostream>
#include <vector>

#include "cmd/all.h"
#include "net/all.h"
#include "types/all.h"
#include "util/all.h"

int main() {
    full_node n = genesis(1, 10'000'000'000);

    std::vector<uint8_t> payload = {0x1, 0x3};

    net_msg msg = net_msg{
        0x05,                                     // msg type = ping
        static_cast<uint8_t>(msg_type::SENDMEM),  // protocol version
        0x02,                                     // length of payload
        payload};                                 // payload

    std::vector<uint8_t> serialized = serialize(msg);
    print_serialized_net_msg(serialized);

    net_msg unserialized = deserialize_msg_header(serialized);
    print_net_msg(unserialized);

    return 0;
}

/*
    REMAINING REFACTORS:
        - CRYPTO: fix sha256 functions, security risk
        - CRYPTO: streamline functions
        - UTIL: streamline conversion functions, fn overloads
        - MAJOR GLOBAL: error codes and error handling
*/