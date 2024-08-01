#include "crypto.h"

#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/ripemd.h>
#include <openssl/sha.h>

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

void init_openssl() {
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
}

std::vector<unsigned char> hex_to_bin(const std::string& hex) {
    // Check if the hex string length is even
    if (hex.length() % 2 != 0) {
        throw std::invalid_argument("Hexadecimal string length must be even.");
    }

    std::vector<unsigned char> binaryData;
    binaryData.reserve(hex.length() / 2);

    // Iterate through each pair of hex digits
    for (size_t i = 0; i < hex.length(); i += 2) {
        // Extract two characters (one byte) from the string
        std::string byteString = hex.substr(i, 2);
        unsigned char byteValue = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16));
        binaryData.push_back(byteValue);
    }

    return binaryData;
}

std::string toHex(const unsigned char* data, size_t len) {
    std::ostringstream oss;
    for (size_t i = 0; i < len; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
    }
    return oss.str();
}

std::string sha256_to_hex(const std::vector<unsigned char>& pubKey) {
    // SHA-256 hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, pubKey.data(), pubKey.size());
    SHA256_Final(hash, &sha256);

    // Convert hash to hex string
    return toHex(hash, SHA256_DIGEST_LENGTH);
}

// uses secp256k1
// no error handling :)
EC_KEY* generate_keys() {
    init_openssl();
    EC_KEY* ec_key = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_generate_key(ec_key);
    return ec_key;
}

std::string get_priv_key(EC_KEY* ec_key) {
    const BIGNUM* priv_key_bn = EC_KEY_get0_private_key(ec_key);
    int priv_key_len = BN_num_bytes(priv_key_bn);
    unsigned char* priv_key_bin = new unsigned char[priv_key_len];
    BN_bn2bin(priv_key_bn, priv_key_bin);
    std::string priv_key_hex = toHex(priv_key_bin, priv_key_len);

    delete[] priv_key_bin;

    return priv_key_hex;
}

std::string get_pub_key(EC_KEY* ec_key) {
    const EC_POINT* pub_key_point = EC_KEY_get0_public_key(ec_key);
    EC_GROUP* ec_group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    int pub_key_len = EC_POINT_point2oct(ec_group, pub_key_point, POINT_CONVERSION_UNCOMPRESSED, nullptr, 0, nullptr);
    unsigned char* pub_key_bin = new unsigned char[pub_key_len];
    EC_POINT_point2oct(ec_group, pub_key_point, POINT_CONVERSION_UNCOMPRESSED, pub_key_bin, pub_key_len, nullptr);
    std::string pub_key_hex = toHex(pub_key_bin, pub_key_len);

    delete[] pub_key_bin;
    EC_GROUP_free(ec_group);

    return pub_key_hex;
}

std::string generate_wallet_address(std::string pub_key_hex) {
    std::string address_hex = sha256_to_hex(hex_to_bin(pub_key_hex));
    const int address_len = 16;
    std::string address = address_hex.substr(address_hex.size() - address_len);
    return address;
}

crypto_keys keygen() {
    crypto_keys keys;
    EC_KEY* ec_key = generate_keys();
    keys.priv_key = get_priv_key(ec_key);
    keys.pub_key = get_pub_key(ec_key);

    return keys;
}

// EC_KEY_free(keys);
// EVP_cleanup();
// ERR_free_strings();
