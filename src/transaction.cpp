#include "transaction.h"

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "crypto.h"

transaction init_transaction(std::string sender, std::string receiver, int64_t amount, int64_t transaction_fee) {
    transaction t;
    t.sender_address = sender;
    t.receiver_address = receiver;
    t.amount = amount;
    t.transaction_fee = transaction_fee;

    return t;
}

void sign_transaction(transaction* t, std::string priv_key, std::string pub_key) {
    // serialize, hash, add script sig and script pub key
    // script sig: signature of transaction + " " + pub key
    // script pub key: double hashed pub key

    // hash and sign transaction
    std::vector<uint8_t> hash_bytes = hash_transaction(t);
    std::vector<uint8_t> signature = transaction_signature(hash_bytes, priv_key);

    // add script sig
    std::string script_sig = bytes_to_hex(signature) + " " + pub_key;
    t->script_sig = script_sig;

    // add script pub key
    std::vector<uint8_t> pub_bytes(pub_key.begin(), pub_key.end());
    std::string script_pub_key = bytes_to_hex(hash_sha256(hash_sha256(pub_bytes)));
    t->script_pub_key = script_pub_key;

    return;
}

std::vector<uint8_t> hash_transaction(transaction* t) {
    // double hash data 😎
    std::vector<uint8_t> bytes = serialize_transaction(t);
    std::vector<uint8_t> hash = hash_sha256(hash_sha256(bytes));
    return hash;
}

std::vector<uint8_t> serialize_transaction(transaction* t) {
    // sender, receiver, amount, transaction
    // implement utxo later

    std::vector<uint8_t> bytes(t->sender_address.begin(), t->sender_address.end());
    bytes.insert(bytes.end(), t->receiver_address.begin(), t->receiver_address.end());

    std::vector<uint8_t> amount_bytes = serialize_uint64(t->amount);
    bytes.insert(bytes.end(), amount_bytes.begin(), amount_bytes.end());

    std::vector<uint8_t> fee_bytes = serialize_uint64(t->transaction_fee);
    bytes.insert(bytes.end(), fee_bytes.begin(), fee_bytes.end());

    return bytes;
}

/*
        HELPER FUNCTIONS
*/

void print_transaction(transaction* t) {
    std::cout << "Sender: " << t->sender_address << std::endl;
    std::cout << "Receiver: " << t->receiver_address << std::endl;
    std::cout << "Amount: " << t->amount << std::endl;
    std::cout << "Transaction Fee: " << t->transaction_fee << std::endl;
    std::cout << "Signature: " << t->script_sig << std::endl;
    std::cout << "PubKey Verification: " << t->script_pub_key << std::endl;

    std::cout << std::endl;

    return;
}

std::vector<uint8_t> serialize_uint64(uint64_t value) {
    std::vector<uint8_t> bytes(8);
    std::memcpy(bytes.data(), &value, 8);
    return bytes;
}

std::string bytes_to_hex(const std::vector<uint8_t>& bytes) {
    std::stringstream ss;
    for (auto byte : bytes) {
        ss << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
    }
    return ss.str();
}
