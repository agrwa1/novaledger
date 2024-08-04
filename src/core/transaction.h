#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "constants.h"
#include "crypto/all.h"

typedef struct tx_in {
    std::string tx_hash;
    std::string sig;
    uint32_t output_idx;

    // sequence number set for now, might implement rbf later
    uint32_t seq_num = 0xFFFFFFFF;
} tx_in;

// an output is a UTXO
typedef struct tx_out {
    uint64_t amt;
    std::string pub_hash;
} tx_out;

// can add locktime later if want to add smart contracts
typedef struct tx {
    // can remove addrs later
    // keeping for wallets to scan through transactions
    std::string s_addr;
    std::string r_addr;
    uint8_t num_input;
    uint8_t num_output;
    std::vector<tx_in> inputs;
    std::vector<tx_out> outputs;

    std::string version = TRANSACTION_VERSION;
} tx;

// tx gen_gns_tx(std::string r_addr, std::string r_pub_key, uint64_t amt);
tx init_tx(std::string s_addr, std::string r_addr, uint8_t num_input, uint8_t num_output, std::vector<tx_in> inputs, std::vector<tx_out> outputs);
std::string hash_tx(tx t);

// need to be able to add transactions
// right now can't lookup utxos by address
// wallets need to store utxo pool locally to quickly make transactions
// wallets sync with nodes and compute current relevant utxos

// typedef struct {
//     std::string sender_address;
//     std::string receiver_address;
//     uint64_t amount;
//     uint64_t transaction_fee;

//     std::string hash;
//     std::string script_sig;
//     std::string script_pub_key;
// } transaction;

// tx init_tx(std::vector<tx_input> inputs, std::vector<tx_output> outputs) {};

// wallets will generate txs from user data and stored data and send to nodes which will propagate

// transaction init_transaction(std::string sender, std::string receiver, int64_t amount, int64_t transaction_fee);

// FIXME - this shits completely fucked
// void sign_transaction(transaction* t, std::string priv_key, std::string pub_key);

// std::vector<uint8_t> hash_transaction(transaction* t);

// std::vector<uint8_t> serialize_transaction(transaction* t);

// bool verify_transaction(transaction* t);

/*
    HELPER FUNCTIONS
*/

std::vector<uint8_t> serialize_uint64(uint64_t value);

#endif