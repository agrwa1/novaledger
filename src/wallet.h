#ifndef WALLET_H
#define WALLET_H

#include <string>

struct wallet {
    std::string pub_key;
    std::string priv_key;
    std::string address;

    wallet(std::string pub, std::string priv, std::string addr) : pub_key(pub), priv_key(priv), address(addr) {}
};

wallet new_wallet();

void print_wallet(wallet);

#endif