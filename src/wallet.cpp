#include "wallet.h"

#include <iostream>
#include <string>
#include <vector>

#include "crypto.h"

wallet new_wallet() {
    crypto_keys keys = keygen();
    std::string wallet_address = generate_wallet_address(keys.pub_key);

    return wallet(keys.pub_key, keys.priv_key, wallet_address);
}

void print_wallet(wallet w) {
    std::cout << "Private Key: " << w.priv_key << std::endl
              << "Public Key: " << w.pub_key << std::endl
              << "Public Address: " << w.address << std::endl;
}