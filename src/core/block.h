#ifndef CORE_BLOCK_H
#define CORE_BLOCK_H

#include <string>
#include <vector>

#include "transaction.h"
// #include "util/all.h"

const int DEFAULT_BLOCK_HASH_DIFFICULTY = 1;
const std::string BLOCK_VERSION = "1.0";

// block needs: timestamp, previous hash, nonce, merkle root hash, transactions, difficulty
struct block {
    uint64_t height;
    std::string prev_hash;
    std::vector<tx> txs;

    uint64_t nonce;
    std::string merkle_root;

    time_t timestamp;
    std::string version = BLOCK_VERSION;

    // extremely easy difficulty for now (no impact on mining)
    // represents number of leading bits to be 0
    uint32_t difficulty = DEFAULT_BLOCK_HASH_DIFFICULTY;
};

block mine_block(uint64_t height, std::string prev_hash, std::vector<tx> txs);

std::string get_merkle_root(std::vector<tx>& txs);
#endif