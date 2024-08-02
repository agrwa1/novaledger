
#include "utxo.h"

#include <string>
#include <unordered_map>
#include <vector>

void add_utxo_to_n_pool(utxo_set& pool, std::string hash, uint32_t idx, uint64_t amt, std::string pub_hash) {
    utxo_key key = utxo_key{hash, idx};
    utxo_val val = utxo_val{amt, pub_hash};
    pool[key] = val;
}

void del_utxo_from_n_pool(utxo_set& pool, std::string hash, uint32_t idx) {
    utxo_key key = utxo_key{hash, idx};
    pool.erase(key);
}

// if returns empty utxo val, then nothing exists
utxo_val get_utxo(utxo_set& pool, std::string hash, uint32_t idx) {
    utxo_val val;

    utxo_key key = utxo_key{hash, idx};
    auto it = pool.find(key);
    if (it != pool.end()) {
        val = it->second;
    }
    return val;
}
