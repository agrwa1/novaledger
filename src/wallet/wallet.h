#ifndef WALLET_H
#define WALLET_H

#include <list>
#include <string>

#include "core/all.h"

// stores relevant utxo data
typedef struct w_utxo {
    std::string tx_hash;
    uint32_t output_idx;
    uint64_t amt;

    std::string sig;

    // TODO: implement timestamps
    // std::time_t tx_mined_at;
} w_utxo;

/* NOTE: UTXO POOL IMPLEMENTATION:
    - list of all active utxos to use
    - add new tokens to end
    - remove tokens from beginning
    - on soft refresh, check most recent
        date from last token
    - on hard refresh, rebuild entire list
*/

struct wallet {
    std::string pub_key;
    std::string priv_key;
    std::string addr;

    // timestamp (don't need to check previous transactions)
    std::time_t last_refresh;
    std::list<w_utxo> pool;

    wallet(std::string pub, std::string priv, std::string addr)
        : pub_key(pub), priv_key(priv), addr(addr) {}
};

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
