#ifndef TYPES_NODE_H
#define TYPES_NODE_H

#include "block.h"

struct full_node {
    blockchain chain;
    // utxo_set pool;
    std::vector<std::string> wallet_addrs;
    std::string primary_addr;
};

#endif