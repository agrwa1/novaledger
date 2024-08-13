#ifndef TYPES_NODE_H
#define TYPES_NODE_H

#include "block.h"
#include "utxo.h"

struct full_node {
    // CORE
    blockchain chain;
    utxo_set pool;

    // WALLET
    std::vector<std::string> wallet_addrs;
    std::string primary_addr;

    // NETWORK
    std::string listen_addr;
};

#endif