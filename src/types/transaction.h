#ifndef TYPES_TRANSACTION_H
#define TYPES_TRANSACTION_H

#include <string>
#include <vector>

#include "constants.h"

struct tx_in {
    std::string tx_hash;
    std::string sig;  // = "signature" "pub key"
    uint32_t output_idx;

    // sequence number set for now, might implement rbf later
    uint32_t seq_num = 0xFFFFFFFF;
};

// an output is a UTXO
struct tx_out {
    uint64_t amt;
    std::string tx_pub_hash;
};

// can add locktime later if want to add smart contracts
struct tx {
    // can remove addrs later
    // keeping for wallets to scan through transactions
    std::string s_addr;
    std::string r_addr;
    uint8_t num_input;
    uint8_t num_output;
    std::vector<tx_in> inputs;
    std::vector<tx_out> outputs;

    std::string version = TRANSACTION_VERSION;
};

typedef std::vector<tx> tx_vec;

#endif