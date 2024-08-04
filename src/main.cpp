#include <iostream>
#include <vector>

#include "core/all.h"
#include "util/all.h"
#include "wallet/all.h"

// implement soft nodes
// hard nodes
// typedef struct node {
//     blockchain chain;
//     utxo_set pool;
//     std::string miner_addr;
// } node;

std::vector<wallet> gen_gns_wallets(int num_wallets) {
    std::vector<wallet> wallets;
    for (int i = 0; i < num_wallets; i++) {
        wallet w = init_wallet();
        wallets.push_back(w);
    }

    return wallets;
}

// create genesis txs
std::vector<tx> gen_gns_txs(std::vector<wallet> wallets, uint64_t amt) {
    std::vector<tx> txs;
    for (auto w : wallets) {
        tx t = gen_gns_tx(w, w.addr, w.pub_key, amt);
        txs.push_back(t);
    }

    return txs;
}

int main() {
    std::vector<wallet> wallets = gen_gns_wallets(2048);
    std::vector<tx> txs = gen_gns_txs(wallets, 10'000'000);

    // for (auto t : txs) {
    //     print_tx(t);
    // }

    blockchain chain = blockchain_gns(txs);
    chain.tx_pool = txs;
    mine_new_block(chain);
    print_blockchain(chain);

    return 0;
}
