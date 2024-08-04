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

// make new block
// used by blockchain
// TODO: add merkle tree
// TODO: Proof of work -> add nonce config
// mine new block
block mine_block(uint64_t height, std::string prev_hash, std::vector<tx> txs) {
    block b;

    // create initial block
    b.height = height;
    b.prev_hash = prev_hash;
    b.txs = txs;
    b.timestamp = std::time(nullptr);

    // security: merkle trees prove that they actually did include a transaction
    // security: provides verification that no data was corrupted or lost
    // efficiency: easier to just send the merkle hash
    // efficiency: soft nodes rely on full nodes to provide verifications
    // privacy: don't have to send all transactions over network

    // create merkle tree
    std::string hash = construct_merkle_tree(txs);
    std::vector<std::string> proof = generate_merkle_proof(txs, hash_tx(txs[2]));
    std::string cur_hash = hash_tx(txs[2]);
    if (merkle_proof_is_valid(proof, hash_tx(txs[2]), 2))
        std::cout << "Proof is valid.";

    // add merkle root hash

    // get_merkle_root(txs);

    // TODO: blockchain needs to update utxo set
    // mine block w nonce

    return b;
}

std::string construct_merkle_tree(std::vector<tx>& txs) {
    // create leaf layer
    // create parent layer:
    //      while parent layer num > 1, go again

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
