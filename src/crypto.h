#ifndef CRYPTO_H
#define CRYPTO_H

#include <openssl/ec.h>

#include <string>
#include <vector>

std::vector<uint8_t> transaction_signature(std::vector<uint8_t> hash, std::string priv_key);

std::vector<uint8_t> hash_sha256(std::vector<uint8_t>);

EC_KEY* generate_keys();
std::string get_priv_key(EC_KEY* ec_key);
std::string get_pub_key(EC_KEY* ec_key);
std::string generate_wallet_address(std::string pub_key_hex);

struct crypto_keys {
    std::string priv_key;
    std::string pub_key;
};

crypto_keys keygen();

#endif