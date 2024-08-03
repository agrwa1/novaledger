#include <string>

#include "crypto.h"
#include "util/all.h"

// TODO: move away from using deprecated sha256_to_hex
// addr len is 16
std::string gen_wallet_addr(std::string pub_key_hex) {
    std::string address_hex = sha256_to_hex(hex_to_bin(pub_key_hex));
    const int address_len = 16;
    std::string address = address_hex.substr(address_hex.size() - address_len);
    return address;
}
