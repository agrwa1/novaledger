#ifndef TYPES_UTXO_H
#define TYPES_UTXO_H

#include <string>
#include <unordered_map>

struct utxo_key {
    std::string prev_tx_hash;
    uint32_t output_idx;

    bool operator==(const utxo_key other) const {
        return prev_tx_hash == other.prev_tx_hash && output_idx == other.output_idx;
    }
};

struct utxo_hash_fn {
    size_t operator()(const utxo_key k) const {
        size_t hash = 0;
        for (auto byte : k.prev_tx_hash) {
            hash = hash * 73 + byte;
        }
        hash = hash * 73 + k.output_idx;
        return hash;
    }
};

struct utxo_val {
    uint64_t amt;
    std::string tx_pub_hash;  // tx hash
    // std::string assoc_addr;  // wallet address associated. should provide pub key to verify that they actually
    // wallets keep track of their own utxos
    // can query full_nodes for entire utxo set
    // check which is there by hashing all utxo_key tx_hashes with their own pk
};

// might want to keep different map for addr lookups
// how to implement? new map would require sender addrs to be public on txs

typedef std::unordered_map<utxo_key, utxo_val, utxo_hash_fn> utxo_set;

#endif