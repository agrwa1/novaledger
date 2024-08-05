#ifndef TYPES_BLOCK_H
#define TYPES_BLOCK_H

#include <string>

#include "constants.h"
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
    tx_vec txs;

    // CALCULATED
    std::string merkle_root;
    uint64_t nonce;
    std::string blk_hash;
};

struct blockchain {
    std::string version = BLOCKCHAIN_VERSION;
    uint32_t difficulty = DEFAULT_BLOCK_HASH_DIFFICULTY;
    std::string cons_mech = CONSENSUS_MECHANISM;
    uint64_t block_mine_reward = 5'000'000'000ULL;

    std::vector<block> ledger;
    tx_vec tx_pool;
    uint32_t height = 0;
};

#endif