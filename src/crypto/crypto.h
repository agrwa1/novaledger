#ifndef CRYPTO_H
#define CRYPTO_H

#include <openssl/ec.h>

#include <string>
#include <vector>

// TODO: organize crypto files

std::vector<uint8_t> hash_sha256(std::vector<uint8_t>);

std::string hash_sha256(std::string raw);

// TODO: split and migrate
std::string sha256_to_hex(const std::vector<unsigned char>& pubKey);

#endif