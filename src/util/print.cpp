
#include <iomanip>
#include <iostream>
#include <vector>

#include "types/all.h"

void print_tx(tx t) {
    std::cout << "From: \"" << t.s_addr << "\"" << std::endl;
    std::cout << "To: \"" << t.r_addr << "\"" << std::endl;

    std::cout << "Inputs: " << t.inputs.size() << std::endl;
    for (auto in : t.inputs) {
        std::cout << "\"" << in.tx_hash << "\"[" << in.output_idx << "]: " << in.sig << std::endl;
    }

    std::cout << "Outputs: " << t.outputs.size() << std::endl;
    for (int i = 0; i < t.outputs.size(); i++) {
        tx_out out = t.outputs[i];
        std::cout << "[" << i << "] Amount: " << out.amt << ". PubKey Hash: " << out.tx_pub_hash << std::endl;
    }
    std::cout << std::endl;
}

void print_wallet(wallet w) {
    std::cout << "Private Key: " << w.priv_key << std::endl
              << "Public Key: " << w.pub_key << std::endl
              << "Public Address: " << w.addr << std::endl;

    for (w_utxo utxo : w.pool) {
        std::cout << "-> \"" << utxo.tx_hash << "\"[" << utxo.output_idx << "] for " << utxo.amt << " nanos.\n\t" << utxo.sig << std::endl;
    }

    std::cout << std::endl;
}

void print_block(block b) {
    std::cout << "Version: " << b.version << std::endl;
    std::cout << b.height << ": \"" << b.prev_hash << "\"" << std::endl;
    std::cout << "Merkle Root Hash: " << b.merkle_root << std::endl;
    std::cout << "Transactions: " << b.txs.size() << std::endl;
    std::cout << "Difficulty: " << b.difficulty << " -> Nonce: " << b.nonce << std::endl;
    std::cout << "Block Hash: " << b.blk_hash << std::endl;
    std::cout << "Prev Block Hash: " << b.prev_hash << std::endl;
}

void print_blockchain(const blockchain& b) {
    std::cout << std::endl;
    for (auto blk : b.ledger) {
        print_block(blk);
        std::cout << std::endl;
    }
}

void print_utxo_key(utxo_key key) {
    std::cout << "Key: " << key.prev_tx_hash << "[" << key.output_idx << "]" << std::endl;
}

void print_utxo_val(utxo_val val) {
    std::cout << "Amount: " << val.amt << std::endl;
    std::cout << "Pub Key Hash: " << val.tx_pub_hash << std::endl;
}

void print_utxo_set(utxo_set& pool) {
    // get all key val pairs
    for (const auto& pair : pool) {
        std::cout << std::endl;
        print_utxo_key(pair.first);
        print_utxo_val(pair.second);
    }
}

void help_print_bytes(std::vector<uint8_t> bytes) {
    for (size_t i = 0; i < bytes.size(); ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
        if (i != bytes.size() - 1) {
            std::cout << " ";
        }
    }
}

void print_bytes(std::vector<uint8_t> bytes) {
    help_print_bytes(bytes);
    std::cout << std::dec << std::endl;  // Reset to decimal after printing
}

void print_serialized_net_msg(std::vector<uint8_t> msg) {
    std::cout << std::dec << "Version: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(msg[0]) << std::endl;

    std::cout << std::dec << "Msg Type: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(msg[1]) << std::endl;

    std::cout << std::dec << "Msg Length: ";
    for (size_t i = 2; i < 6; ++i) {
        std::cout << std::hex << static_cast<int>(msg[i]) << " ";
    }

    std::cout << std::endl;

    std::cout << std::dec << "Body (w/ length): ";
    for (size_t i = 6; i < msg.size(); ++i) {
        std::cout << std::hex << static_cast<int>(msg[i]) << " ";
    }

    std::cout << std::dec << std::endl;
}

void print_net_msg(net_msg msg) {
    std::cout << "Message in decimal: " << std::endl;
    std::cout << "Version: " << std::dec << static_cast<int>(msg.protocol_version) << std::endl;
    std::cout << "Type: " << std::dec << static_cast<int>(msg.type) << std::endl;
    std::cout << "Length: " << std::dec << static_cast<int>(msg.length) << std::dec << std::endl;
}