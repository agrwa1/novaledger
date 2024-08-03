#ifndef CRYPTO_TRANSACTION_H
#define CRYPTO_TRANSACTION_H

#include <string>
#include <vector>

// std::vector<uint8_t> transaction_signature(std::vector<uint8_t> hash, std::string priv_key);
// change to sign_tx
std::vector<uint8_t> sign_tx(std::vector<uint8_t> hash, std::string priv_key);

#endif