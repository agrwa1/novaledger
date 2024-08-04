#ifndef CORE_BLOCKCHAIN_H
#define CORE_BLOCKCHAIN_H

#include <vector>

#include "constants.h"
#include "core/all.h"

typedef struct blockchain {
    std::string version = BLOCKCHAIN_VERSION;
    uint32_t difficulty = DEFAULT_BLOCK_HASH_DIFFICULTY;
    std::string cons_mech = CONSENSUS_MECHANISM;
    uint32_t block_mine_reward = 5'000'000'000;

    std::vector<block> ledger;
    std::vector<tx> tx_pool;
    uint32_t height = 0;

} blockchain;

block mine_new_block(blockchain& chain);

blockchain blockchain_gns(std::vector<tx>& txs);
#endif