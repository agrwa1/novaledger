#ifndef CRYPTO_KEY_H
#define CRYPTO_KEY_H

#include <openssl/ec.h>

#include <string>

#include "crypto.h"

struct crypto_keys {
    std::string priv_key;
    std::string pub_key;
};

crypto_keys keygen();

EC_KEY* generate_keys();

std::string get_priv_key(EC_KEY* ec_key);

std::string get_pub_key(EC_KEY* ec_key);

#endif