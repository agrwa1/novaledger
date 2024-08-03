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
    std::vector<tx> gns_txs;
    utxo_set pool;

    // create wallets
    for (int i = 0; i < 5; i++) {
        // initialize genesis wallet addrs
        wallet w = init_wallet();

        // create genesis transactions for each
        tx gns_tx = gen_gns_tx(w, w.addr, w.pub_key, 5'000'000);
        // std::cout << "Wallet balance: " << get_balance(w.pool) << std::endl;
        // print_tx(gns_tx);

        if (i == 0) {
            print_wallet(w);
        }

        // print_wallet(w);
        wallets.push_back(w);

        // add tokens to wallet pool
        // gns tx only has one
    }

    print_wallet(wallets[0]);

    // check initial balance
    std::cout << "Balance: " << get_balance(wallets[0].pool) << std::endl;

    // add utxo to wallet[0] pool. only valid for genesis
    // generating genesis transactions -> first wallets

    // std::vector<w_utxo> gns_utxos {
    //     w_utxo {
    //         "",
    //     }

    // };

    // tx from w1 to
    // tx t1 = create_tx(wallets[0], wallets[1].addr, wallets[1].pub_key, 1'000'000);

    // print_tx(t1);
    // std::cout << "main " << std::endl;
    // print_wallet(wallets[0]);
    // print_wallet(wallets[1]);

    // NOTE: other users public keys aren't publicly available

    // initial wallets now has 5 wallets to address from
    // issuing 50 bitcoin to start; 10 for each wallet

    return 0;
}
