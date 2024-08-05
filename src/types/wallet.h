#ifndef TYPES_WALLET_H
#define TYPES_WALLET_H

#include <list>
#include <string>
#include <vector>

// stores relevant utxo data
// for wallet storage records, doesn't actually count for anything
struct w_utxo {
    std::string tx_hash;
    uint32_t output_idx;
    uint64_t amt;

    std::string sig;

    // TODO: implement timestamps
    // std::time_t tx_mined_at;
};

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

typedef std::vector<wallet> wallet_vec;

#endif