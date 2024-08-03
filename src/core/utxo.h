#ifndef UTXO_H
#define UTXO_H

#include <string>
#include <unordered_map>
#include <vector>

typedef struct utxo_key {
    std::string hash;
    uint32_t idx;

    bool operator==(const utxo_key other) const {
        return hash == other.hash && idx == other.idx;
    }
} utxo_key;

typedef struct utxo_hash_fn {
    size_t operator()(const utxo_key k) const {
        size_t hash = 0;
        for (auto byte : k.hash) {
            hash = hash * 73 + byte;
        }
        hash = hash * 73 + k.idx;
        return hash;
    }
} utxo_hash_fn;

typedef struct utxo_val {
    uint64_t amt;
    std::string pub_hash;
} utxo_val;

typedef std::unordered_map<utxo_key, utxo_val, utxo_hash_fn> utxo_set;

// REVIEW: does this work??
void add_utxo_to_n_pool(utxo_set& pool, std::string hash, uint32_t idx, uint64_t amt, std::string pub_hash);

void del_utxo_from_n_pool(utxo_set& pool, std::string hash, uint32_t idx);

// if returns empty utxo val, then nothing exists
utxo_val get_utxo(utxo_set& pool, std::string hash, uint32_t idx);

#endif