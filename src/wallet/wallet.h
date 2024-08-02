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

wallet init_wallet();

uint64_t get_balance(std::list<w_utxo> pool);

// hardcoded for now, implement with networks
// after hard syncing with full node,
// verify all utxo in pool are valid in node pool
void hard_sync_wallet(wallet&);  // refresh

// add to pool

// FIXME: update create tx to use atomic updates
// remove from pool

// create transactions: wallet, r addr, amt
tx create_tx(wallet& w, const std::string& r_addr, std::string r_pub, const uint64_t& amt);

/*
    HELPER FUNCTIONS
*/

// calculate current amt of coin
uint64_t get_balance(std::vector<w_utxo>&);

#endif