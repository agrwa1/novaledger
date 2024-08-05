#include "crypto.h"

#include <openssl/sha.h>

#include <vector>

#include "util/all.h"

// TODO: figure out why openssl sha256() is retarded. keeps segfaulting.
std::vector<uint8_t> hash_sha256(std::vector<uint8_t> raw) {
    if (raw.empty()) {
        throw std::invalid_argument("Input data is empty.");
    }

    std::vector<uint8_t> hash(SHA256_DIGEST_LENGTH);

    // Initialize the SHA256 context
    SHA256_CTX sha256;
    if (!SHA256_Init(&sha256)) {
        throw std::runtime_error("Failed to initialize SHA256 context.");
    }

    // Update the SHA256 context with data
    if (!SHA256_Update(&sha256, raw.data(), raw.size())) {
        throw std::runtime_error("Failed to update SHA256 context.");
    }

    // Finalize the SHA256 hash
    if (!SHA256_Final(hash.data(), &sha256)) {
        throw std::runtime_error("Failed to finalize SHA256 hash.");
    }

    return hash;
}

std::string hash_sha256(std::string raw) {
    std::vector<uint8_t> raw_bytes(raw.begin(), raw.end());
    std::vector<uint8_t> bytes = hash_sha256(raw_bytes);

    return bytes_to_hex(bytes);
}

std::string sha256_to_hex(const std::vector<unsigned char>& pubKey) {
    // SHA-256 hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, pubKey.data(), pubKey.size());
    SHA256_Final(hash, &sha256);

    // Convert hash to hex string
    return to_hex(hash, SHA256_DIGEST_LENGTH);
}
