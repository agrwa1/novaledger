#include "crypto.h"

#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/ripemd.h>
#include <openssl/sha.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "util/all.h"

std::vector<uint8_t> sign_tx(std::vector<uint8_t> hash, std::string priv_key) {
    // Convert hex private key to binary
    std::vector<uint8_t> priv_key_bin(priv_key.size() / 2);
    for (size_t i = 0; i < priv_key.size(); i += 2) {
        priv_key_bin[i / 2] = (uint8_t)((std::stoi(priv_key.substr(i, 2), nullptr, 16)) & 0xFF);
    }

    // Create EC key
    EC_KEY* ec_key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);  // Use the curve for Bitcoin

    // Load the private key
    BIGNUM* priv_bn = BN_bin2bn(priv_key_bin.data(), priv_key_bin.size(), nullptr);
    EC_KEY_set_private_key(ec_key, priv_bn);

    // Create the ECDSA signature
    ECDSA_SIG* sig = ECDSA_do_sign(hash.data(), hash.size(), ec_key);
    if (!sig) {
        EC_KEY_free(ec_key);
        BN_free(priv_bn);
        throw std::runtime_error("Failed to create ECDSA signature");
    }

    // Convert the signature to DER format
    unsigned int sig_len = i2d_ECDSA_SIG(sig, nullptr);
    std::vector<uint8_t> der_sig(sig_len);
    unsigned char* sig_ptr = der_sig.data();
    i2d_ECDSA_SIG(sig, &sig_ptr);

    // Clean up
    ECDSA_SIG_free(sig);
    EC_KEY_free(ec_key);
    BN_free(priv_bn);

    return der_sig;
}

void init_openssl() {
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
}

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

// TODO: move away from using deprecated sha256_to_hex
std::string generate_wallet_address(std::string pub_key_hex) {
    std::string address_hex = sha256_to_hex(hex_to_bin(pub_key_hex));
    const int address_len = 16;
    std::string address = address_hex.substr(address_hex.size() - address_len);
    return address;
}
