#ifndef CORE_BLOCK_H
#define CORE_BLOCK_H

#include <string>
#include <vector>

// #include "util/all.h"
#include "constants.h"
// #include "core/all.h"
#include "transaction.h"

// block needs: timestamp, previous hash, nonce, merkle root hash, transactions, difficulty
struct block {
    // CONSTANT/AUTOMATIC
    time_t timestamp;
    std::string version = BLOCK_VERSION;
    uint32_t difficulty = DEFAULT_BLOCK_HASH_DIFFICULTY;

    // PROVIDED
    uint64_t height;
    std::string prev_hash;
    std::vector<tx> txs;

    // CALCULATED
    std::string merkle_root;
    uint64_t nonce;
    std::string blk_hash;
};

std::string construct_merkle_tree(std::vector<tx>& txs);

std::string hash_block(block b);

std::vector<std::string> generate_merkle_proof(std::vector<tx> txs, std::string target_tx_hash);

bool merkle_proof_is_valid(std::vector<std::string> proof, std::string target_hash, uint32_t index);
#endif