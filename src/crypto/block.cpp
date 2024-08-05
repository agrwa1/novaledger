
#include <string>
#include <vector>

#include "crypto.h"
#include "types/all.h"
#include "util/all.h"

std::string hash_block(block b) {
    std::vector<uint8_t> serialized_block = serialize(b);
    std::string blk_hash = bytes_to_hex(hash_sha256(hash_sha256(serialized_block)));
    return blk_hash;
}