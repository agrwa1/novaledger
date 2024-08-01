#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "crypto.h"

// input, output, signature, metadata
// sender, receiver, amount, signature, transaction_fee
//* implementing UTXO later

typedef struct {
    std::string sender_address;
    std::string receiver_address;
    uint64_t amount;
    uint64_t transaction_fee;

    std::string script_sig;
    std::string script_pub_key;
} transaction;

transaction init_transaction(std::string sender, std::string receiver, int64_t amount, int64_t transaction_fee);

void sign_transaction(transaction* t, std::string priv_key, std::string pub_key);

std::vector<uint8_t> hash_transaction(transaction* t);

std::vector<uint8_t> serialize_transaction(transaction* t);

/*
    HELPER FUNCTIONS
*/
void print_transaction(transaction* t);

std::vector<uint8_t> serialize_uint64(uint64_t value);

std::string bytes_to_hex(const std::vector<uint8_t>& bytes);

#endif