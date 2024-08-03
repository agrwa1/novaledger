#include <openssl/evp.h>

#include "crypto/all.h"
#include "util/all.h"

// crypto_keys keygen() {
//     crypto_keys keys;
//     EC_KEY* ec_key = generate_keys();
//     keys.priv_key = get_priv_key(ec_key);
//     keys.pub_key = get_pub_key(ec_key);

//     return keys;
// }

// uses secp256k1
// no error handling :)
crypto_keys gen_keys() {
    crypto_keys keys;
    EC_KEY* ec_key = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_generate_key(ec_key);

    keys.priv_key = get_priv_key(ec_key);
    keys.pub_key = get_pub_key(ec_key);

    return keys;
}

std::string get_priv_key(EC_KEY* ec_key) {
    const BIGNUM* priv_key_bn = EC_KEY_get0_private_key(ec_key);
    int priv_key_len = BN_num_bytes(priv_key_bn);
    unsigned char* priv_key_bin = new unsigned char[priv_key_len];
    BN_bn2bin(priv_key_bn, priv_key_bin);
    std::string priv_key_hex = to_hex(priv_key_bin, priv_key_len);

    delete[] priv_key_bin;

    return priv_key_hex;
}

std::string get_pub_key(EC_KEY* ec_key) {
    const EC_POINT* pub_key_point = EC_KEY_get0_public_key(ec_key);
    EC_GROUP* ec_group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    int pub_key_len = EC_POINT_point2oct(ec_group, pub_key_point, POINT_CONVERSION_UNCOMPRESSED, nullptr, 0, nullptr);

    unsigned char* pub_key_bin = new unsigned char[pub_key_len];
    EC_POINT_point2oct(ec_group, pub_key_point, POINT_CONVERSION_UNCOMPRESSED, pub_key_bin, pub_key_len, nullptr);
    std::string pub_key_hex = to_hex(pub_key_bin, pub_key_len);

    delete[] pub_key_bin;
    EC_GROUP_free(ec_group);

    return pub_key_hex;
}
