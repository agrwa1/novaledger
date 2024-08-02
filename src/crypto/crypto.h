#ifndef CRYPTO_H
#define CRYPTO_H

#include <openssl/ec.h>

#include <string>
#include <vector>

// TODO: organize crypto files
// std::vector<uint8_t> transaction_signature(std::vector<uint8_t> hash, std::string priv_key);
// change to sign_tx
std::vector<uint8_t> sign_tx(std::vector<uint8_t> hash, std::string priv_key);

std::vector<uint8_t> hash_sha256(std::vector<uint8_t>);

std::string generate_wallet_address(std::string pub_key_hex);

// TODO: split and migrate
std::string sha256_to_hex(const std::vector<unsigned char>& pubKey);

#endif