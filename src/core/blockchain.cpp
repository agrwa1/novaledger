#include <iostream>

#include "core/utxo.h"
#include "crypto/all.h"
#include "types/all.h"
#include "util/all.h"

// TODO: add block mine reward to node wallet address
// TODO: Proof of work -> add nonce config
// TODO: create algo for best tx computation
void mine_new_block(full_node* node) {
    block b;
    block mrb = node->chain.ledger[node->chain.height];

    b.height = node->chain.height + 1;
    b.prev_hash = mrb.blk_hash;
    b.txs = node->chain.tx_pool;
    b.timestamp = std::time(nullptr);

    std::string hash = construct_merkle_tree(node->chain.tx_pool);
    b.merkle_root = hash;

    b.nonce = 0;
    b.blk_hash = hash_block(b);

    // calculate utxo updates
    bool utxo_update_worked = update_utxo_set_from_block(node->pool, b);
    if (!utxo_update_worked) {
        std::cout << "UTXO in transactions invalid. Discarding block" << std::endl;
        return;
    }

    // update node state
    node->chain.ledger.push_back(b);
    node->chain.height += 1;
    node->chain.tx_pool = {};
}

// add tx to pool
// only update utxo pool on block add -- sentinel program
// TODO: validate txs on addition
void add_tx_to_blkchn_pool(blockchain& chain, tx t) {
    chain.tx_pool.push_back(t);
}

void add_txs_to_blkchn_pool(blockchain& chain, tx_vec txs) {
    for (auto t : txs) {
        add_tx_to_blkchn_pool(chain, t);
    }
}
