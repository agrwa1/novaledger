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
    // add merkle root hash

    get_merkle_root(txs);

    // TODO: blockchain needs to update utxo set
    // mine block w nonce

    return b;
}

// need to memoize
std::string get_merkle_root(std::vector<tx>& txs) {
    uint32_t num_txs = static_cast<uint32_t>(txs.size());
    uint32_t num_leaf_nodes = num_txs + (num_txs % 2);

    // get total node count
    uint32_t total_node_count = num_leaf_nodes;
    uint32_t layer_nodes = num_leaf_nodes / 2;
    while (layer_nodes > 1) {
        total_node_count += layer_nodes;
        layer_nodes = (layer_nodes + (layer_nodes % 2)) / 2;
    }

    total_node_count++;

    std::cout << total_node_count << std::endl;

    std::unordered_map<uint32_t, std::string> map;

    uint32_t num_layer_nodes = num_leaf_nodes;
    int cur_layer_extra_node = num_txs % 2;
    uint32_t cur_node_index = 1;

    while (cur_node_index < total_node_count) {
        // layer logic

        // if <= num_layer_nodes, get hash
        if (cur_node_index <= num_layer_nodes) {
            std::string hash;
            if (cur_node_index < num_leaf_nodes) {
                // hash tx
                uint32_t l_ind = std::min(cur_node_index, num_txs);
                hash = hash_tx(txs[l_ind]);
            } else {
                // need to hash below or across
                // if (cur_node_index == )
            }

            // add to map
        }

        // else move up layer

        cur_node_index++;
    }

    return "";

    // uint32_t cur_num_nodes = num_leaf_nodes;
    // std::string max_hash;

    // while (cur_num_nodes < total_node_count) {

    // }
}

// fuck me
// uint32_t merkle_min_hash(uint32_t index, size_t size) {
//     return std::min(index, static_cast<uint32_t>(size));
// }

// std::string merkle_root_hash_recurse(uint32_t index, std::vector<tx>& txs) {
//     // check if at leaf layer
//     // no: go down -> hash left and right together, yes: start hash node

//     // check if leaf or internal
//     // leaf if parent level < tx.size() && left child level > tx.size();

//     // if leaf layer

//     uint32_t two_multiple = 1;
//     while (two_multiple <= index) {
//         two_multiple *= 2;
//     }

//     uint32_t num_txs = static_cast<uint32_t>(txs.size());

//     // if current line holds
//     if ((two_multiple / 2) >= txs.size()) {
//         // hash transaction
//         // need to get index of closest lowest multiple of 2
//         uint32_t ret_ind = std::min(index, num_txs) - 1;
//         std::string hash = hash_tx(txs[ret_ind]);
//         std::cout << index << ": " << hash << std::endl;
//         return hash;
//     }

//     // std::string left_hash = merkle_root_hash_recurse(merkle_min_hash(index * 2, txs.size()), txs);
//     // std::string right_hash = merkle_root_hash_recurse(merkle_min_hash(index * 2 + 1, txs.size()), txs);
//     std::string left_hash = merkle_root_hash_recurse(index * 2, txs);
//     std::string right_hash = merkle_root_hash_recurse(index * 2 + 1, txs);

//     std::string hash = hash_sha256(left_hash + right_hash);

//     std::cout << index << ": " << index * 2 << " + " << index * 2 + 1 << " -> " << hash << std::endl;
//     return hash;
// }