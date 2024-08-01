#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <stdio.h>

#include <iostream>

#include "block.h"
#include "transaction.h"
#include "wallet.h"

typedef std::vector<block> blockchain;

struct full_node {
    blockchain chain;
    // utxo set
};

int main() {
    wallet w = new_wallet();
    print_wallet(w);

    return 0;
}
