#ifndef CRYPTO_TRANSACTION_H
#define CRYPTO_TRANSACTION_H

#include <string>
#include <vector>

#include "types/all.h"

std::vector<uint8_t> sign_tx(std::vector<uint8_t> hash, std::string priv_key);

std::string hash_tx(tx t);

#endif