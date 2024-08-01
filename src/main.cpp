#include <iostream>
#include <vector>

#include "block.h"
#include "transaction.h"
#include "wallet.h"

typedef std::vector<block> blockchain;

typedef struct {
    blockchain chain;
    // utxo set
} full_node;

int main() {
    // wallet w = new_wallet();
    // print_wallet(w);

    std::vector<wallet> initial_wallets;
    std::vector<transaction> gen_transactions;

    for (int i = 0; i < 5; i++) {
        wallet w = new_wallet();
        // print_wallet(w);
        initial_wallets.push_back(w);

        // genesis block has no sender address
        transaction t = init_transaction("", w.address, 5'000'000, 0);
        sign_transaction(&t, w.priv_key, w.pub_key);

        print_transaction(&t);
        gen_transactions.push_back(t);
    }

    // initial wallets now has 5 wallets to address from
    // issuing 50 bitcoin to start; 10 for each wallet

    return 0;
}
