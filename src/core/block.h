#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>

#include "transaction.h"

// block needs: timestamp, previous hash, nonce, merkle root hash, transactions, difficulty
struct block {
    long long int height;
    std::string timestamp;
    std::string previous_hash;
    long long int nonce;
    std::vector<tx> txs;
    // std::string merkle_root;
    std::string hash;
};

#endif