#include <vector>

#include "crypto.h"
#include "openssl/ec.h"
#include "openssl/pem.h"
#include "types/all.h"
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

std::string hash_tx(tx t) {
    // NOTE: PURPOSEFULLY NOT SERIALZING S_ADDR OR R_ADDR BC PLAN ON LATER REMOVING FIELDS
    // serialize transaction -> double hash results
    std::vector<uint8_t> serialized_tx = serialize(t);
    std::string hashed_tx = bytes_to_hex(hash_sha256(hash_sha256(serialized_tx)));
    return hashed_tx;
}