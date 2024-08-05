#include <iostream>

#include "crypto/all.h"
#include "types/all.h"

// TODO: add block mine reward to node wallet address
// TODO: Proof of work -> add nonce config
block mine_new_block(blockchain& chain) {
    // TODO: create algo for best tx computation
    // add all txs in tx pool
    block b;
    block mrb = chain.ledger[chain.height];

    b.height = chain.height + 1;
    b.prev_hash = mrb.blk_hash;
    b.txs = chain.tx_pool;
    b.timestamp = std::time(nullptr);

    std::string hash = construct_merkle_tree(chain.tx_pool);
    b.merkle_root = hash;

    // TODO: blockchain needs to update utxo set
    // TODO: Proof of work -> nonce config
    b.nonce = 0;

    // hash block -> block
    b.blk_hash = hash_block(b);

    // update chain
    chain.ledger.push_back(b);
    chain.height += 1;
    chain.tx_pool = {};

    return b;
}

// add tx to pool
// only update utxo pool on block add -- sentinel program
void add_tx_to_blkchn_pool(blockchain& chain, tx t) {
    chain.tx_pool.push_back(t);
}

void add_tx_to_blkchn_pool(blockchain& chain, tx_vec txs) {
    for (auto t : txs) {
        chain.tx_pool.push_back(t);
    }
}

// auto miner ??
