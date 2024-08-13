#ifndef CORE_POW_H
#define CORE_POW_H

#include <string>

#include "types/all.h"

// generate target hash value
std::string gen_target_hash(uint32_t difficulty);

// validate target_hash matches difficulty
bool validate_block_pow(block& b);

// POW hash block and find nonce
uint64_t pow_mine_block(block& b);

// validate block

// LATER: adjust difficulty

#endif