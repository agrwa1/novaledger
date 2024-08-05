#ifndef TYPES_UTXO_H
#define TYPES_UTXO_H

#include <string>
#include <unordered_map>

struct utxo_key {
    std::string hash;
    uint32_t idx;

    bool operator==(const utxo_key other) const {
        return hash == other.hash && idx == other.idx;
    }
};

struct utxo_hash_fn {
    size_t operator()(const utxo_key k) const {
        size_t hash = 0;
        for (auto byte : k.hash) {
            hash = hash * 73 + byte;
        }
        hash = hash * 73 + k.idx;
        return hash;
    }
};

struct utxo_val {
    uint64_t amt;
    std::string pub_hash;
};

typedef std::unordered_map<utxo_key, utxo_val, utxo_hash_fn> utxo_set;

#endif