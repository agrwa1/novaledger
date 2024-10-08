#ifndef CRYPTO_KEY_H
#define CRYPTO_KEY_H

#include <openssl/ec.h>

#include <string>

#include "crypto.h"
#include "types/all.h"

crypto_keys gen_keys();
std::string get_priv_key(EC_KEY* ec_key);
std::string get_pub_key(EC_KEY* ec_key);

#endif