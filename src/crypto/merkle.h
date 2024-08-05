#ifndef CRYPTO_MERKLE_H
#define CRYPTO_MERKLE_H

#include <string>
#include <vector>

#include "types/all.h"

std::vector<std::string> generate_merkle_proof(tx_vec txs, std::string target_tx_hash);
bool merkle_proof_is_valid(std::vector<std::string> proof, std::string target_hash, uint32_t index);
std::string construct_merkle_tree(tx_vec& txs);

#endif