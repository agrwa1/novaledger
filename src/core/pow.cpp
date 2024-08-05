
#include <string>

#include "crypto/all.h"
#include "types/all.h"

// generate target hash value
// using define difficulty in number of starting 0s
std::string gen_target_hash(uint32_t difficulty) {
    // SHA256 has 64 hex chars in hash
    std::string target = "";
    for (int i = 0; i < 64; i++) {
        if (i < difficulty) {
            target.push_back('0');
        } else {
            target.push_back('f');
        }
    }

    return target;
}

// TODO: validate other parts of the block
//  validate target_hash matches difficulty
bool validate_block_pow(block& b) {
    // check if less than or equal to gen_target_hash
    std::string blk_hash = hash_block(b);

    if (blk_hash <= gen_target_hash(b.difficulty)) {
        return true;
    }

    return false;
}

// POW hash block and find nonce
// TODO: optimize this
std::string pow_mine_block(block& b) {
    std::string blk_hash;
    for (; true;) {
        if (validate_block_pow(b)) break;
        b.nonce += 1;
    }

    return blk_hash;
}
