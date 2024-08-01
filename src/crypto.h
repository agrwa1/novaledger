#ifndef CRYPTO_H
#define CRYPTO_H

#include <openssl/ec.h>

#include <string>

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