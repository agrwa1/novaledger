#ifndef WALLET_MAIN_H
#define WALLET_MAIN_H

#include <list>
#include <string>

#include "types/all.h"

// FIXME: update create tx to use atomic updates
// create transactions: wallet, r addr, amt
tx create_tx(wallet& w, const std::string& r_addr, std::string r_pub, const uint64_t& amt);

// FIXME - when implemented syncing and w_pool updates, remove wallet param
tx gen_gns_tx(wallet& w, std::string r_addr, std::string r_pub_key, uint64_t amt);

void add_utxo_to_w_pool(wallet& w, const std::string& tx_hash, const uint32_t& output_idx, const uint64_t& amt);

/*
    HELPER FUNCTIONS
*/

uint64_t get_balance(std::list<w_utxo> pool);

// void init_wallet(wallet& w);
wallet init_wallet();

/*
    TODO
*/

// hardcoded for now, implement with networks
// after hard syncing with full node,
// verify all utxo in pool are valid in node pool
// void hard_sync_wallet(wallet&);  // refresh
// void soft_sync wallet

// remove from pool

#endif
