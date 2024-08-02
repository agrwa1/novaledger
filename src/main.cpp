#include <iostream>
#include <vector>

#include "core/all.h"
#include "util/all.h"
#include "wallet/all.h"

typedef std::vector<block> blockchain;

// hard nodes
typedef struct {
    blockchain chain;
    utxo_set pool;
    std::string miner_addr;
} node;

// implement soft nodes

int main() {
    std::vector<wallet> wallets;
    std::vector<tx> gen_transactions;
    utxo_set pool;

    // create wallets
    for (int i = 0; i < 5; i++) {
        wallet w = init_wallet();
        // print_wallet(w);
        wallets.push_back(w);
    }

    // create some transactions from them
    std::cout << get_balance(wallets[0].pool) << std::endl;

    // tx from w1 to
    tx t1 = create_tx(wallets[0], wallets[1].addr, wallets[1].pub_key, 1'000'000);

    print_tx(t1);
    std::cout << "main " << std::endl;
    print_wallet(wallets[0]);
    print_wallet(wallets[1]);

    // NOTE: other users public keys aren't publicly available

    // initial wallets now has 5 wallets to address from
    // issuing 50 bitcoin to start; 10 for each wallet

    return 0;
}
