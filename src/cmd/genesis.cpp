
#include "genesis.h"

#include <iostream>
#include <vector>

#include "core/all.h"
#include "crypto/all.h"
#include "types/all.h"
#include "util/all.h"
#include "wallet/all.h"

// entire genesis: returns node
full_node genesis(uint32_t num_wallets, uint64_t amt) {
    wallet_vec wallets = gen_gns_wallets(num_wallets);
    tx_vec txs = gen_gns_txs(wallets, amt);

    blockchain chain = blockchain_gns(txs);
    add_txs_to_blkchn_pool(chain, txs);
    // print_blockchain(chain);

    full_node n;
    n.chain = chain;

    // update utxo set
    update_utxo_set_from_block(n.pool, n.chain.ledger[0]);
    return n;
}

wallet_vec gen_gns_wallets(uint32_t num_wallets) {
    wallet_vec wallets;
    for (int i = 0; i < num_wallets; i++) {
        wallet w = init_wallet();
        wallets.push_back(w);
    }

    return wallets;
}

// create genesis txs
tx_vec gen_gns_txs(wallet_vec wallets, uint64_t amt) {
    tx_vec txs;
    for (auto w : wallets) {
        tx t = gen_gns_tx(w, w.addr, w.pub_key, amt);
        txs.push_back(t);
    }

    return txs;
}

// init new blockchain (genesis)
blockchain blockchain_gns(tx_vec& txs) {
    blockchain chain;
    block blk;

    blk.timestamp = time_t(nullptr);
    blk.height = 0;
    blk.prev_hash = "";
    blk.txs = txs;

    // calculate merkle tree
    std::string merkle_root_hash = construct_merkle_tree(txs);
    blk.merkle_root = merkle_root_hash;

    blk.blk_hash = hash_block(blk);

    // Proof of work comps
    blk.nonce = 0;
    uint64_t nonce = pow_mine_block(blk);
    print_block(blk);

    // add block to chain
    chain.ledger.push_back(blk);
    chain.tx_pool = {};

    return chain;
}