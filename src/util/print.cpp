
#include <iostream>

#include "wallet/all.h"

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
        std::cout << "[" << i << "] Amount: " << out.amt << ". PubKey Hash: " << out.pub_hash << std::endl;
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

    std::cout << std::endl
              << std::endl;
}
