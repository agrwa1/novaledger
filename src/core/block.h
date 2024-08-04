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

struct merkle_proof_node {
    std::string hash;
    bool after;
};

block mine_block(uint64_t height, std::string prev_hash, std::vector<tx> txs);

std::string construct_merkle_tree(std::vector<tx>& txs);

std::vector<std::string> generate_merkle_proof(std::vector<tx> txs, std::string target_tx_hash);

bool merkle_proof_is_valid(std::vector<std::string> proof, std::string target_hash, uint32_t index);
#endif