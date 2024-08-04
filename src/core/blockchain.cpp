#include <iostream>

#include "core/all.h"
#include "util/all.h"

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
// auto miner

// init new blockchain (genesis)
blockchain blockchain_gns(std::vector<tx>& txs) {
    blockchain chain;
    block blk;

    blk.timestamp = time_t(nullptr);
    blk.height = 0;
    blk.prev_hash = "";
    blk.txs = txs;

    // calculate merkle tree
    std::string merkle_root_hash = construct_merkle_tree(txs);
    blk.merkle_root = merkle_root_hash;

    blk.nonce = 0;
    blk.blk_hash = hash_block(blk);

    // add block to chain
    chain.ledger.push_back(blk);
    chain.tx_pool = {};

    return chain;
}