#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/all.h"
#include "crypto/all.h"
#include "util/all.h"

std::string hash_block(block b) {
    std::vector<uint8_t> serialized_block = serialize(b);
    std::string blk_hash = bytes_to_hex(hash_sha256(hash_sha256(serialized_block)));
    return blk_hash;
}

// security: merkle trees prove that they actually did include a transaction
// security: provides verification that no data was corrupted or lost
// efficiency: easier to just send the merkle hash
// efficiency: soft nodes rely on full nodes to provide verifications
// privacy: don't have to send all transactions over network

std::string construct_merkle_tree(std::vector<tx>& txs) {
    std::vector<std::string> leaf_nodes;
    for (auto t : txs) {
        leaf_nodes.push_back(hash_tx(t));
    }

    while (leaf_nodes.size() > 1) {
        std::vector<std::string> parent_nodes;

        for (uint32_t i = 0; i < leaf_nodes.size(); i += 2) {
            if (i + 1 < leaf_nodes.size()) {
                // next node exists
                parent_nodes.push_back(hash_sha256(leaf_nodes[i] + leaf_nodes[i + 1]));
            } else {
                parent_nodes.push_back(hash_sha256(leaf_nodes[i] + leaf_nodes[i]));
            }
        }

        leaf_nodes = parent_nodes;
    }

    return leaf_nodes[0];
}

std::vector<std::string> generate_merkle_proof(std::vector<tx> txs, std::string target_tx_hash) {
    int32_t target_idx = -1;
    std::vector<std::string> leaf_nodes;

    for (int i = 0; i < txs.size(); i++) {
        if (hash_tx(txs[i]) == target_tx_hash) {
            target_idx = i;
        }
        leaf_nodes.push_back(hash_tx(txs[i]));
    }

    if (target_idx == -1)
        return {};

    // go thrpugh each layer and append to sibling nodes
    std::vector<std::string> siblings;

    while (leaf_nodes.size() > 1) {
        std::vector<std::string> parents;
        for (int i = 0; i < leaf_nodes.size(); i += 2) {
            if (i + 1 < leaf_nodes.size()) {
                parents.push_back(hash_sha256(leaf_nodes[i] + leaf_nodes[i + 1]));
            } else {
                parents.push_back(hash_sha256(leaf_nodes[i] + leaf_nodes[i]));
            }
        }

        // sibling calc
        int sibling_idx = (target_idx % 2 == 0) ? target_idx + 1 : target_idx - 1;

        if (sibling_idx < leaf_nodes.size()) {
            siblings.push_back(leaf_nodes[sibling_idx]);

        } else
            siblings.push_back(leaf_nodes[target_idx]);

        target_idx /= 2;
        leaf_nodes = parents;
    }

    siblings.push_back(leaf_nodes[0]);

    return siblings;
}

bool merkle_proof_is_valid(std::vector<std::string> proof, std::string target_hash, uint32_t index) {
    // while target_kk
    for (auto p : proof) {
        if (target_hash == p)
            return true;

        if (index % 2 == 0) {
            // combine right
            target_hash = hash_sha256(target_hash + p);
        } else {
            target_hash = hash_sha256(p + target_hash);
        }

        index /= 2;
    }

    return false;
}
