
#include <iostream>

#include "wallet/all.h"

void print_tx(tx t) {
    std::cout << "\"" << t.s_addr << "\" -> \"" << t.r_addr << "\"/\n"
              << std::endl;
    for (auto in : t.inputs) {
        std::cout << "\"" << in.tx_hash << "\"[" << in.output_idx << "]: " << in.sig << std::endl;
    }
    for (auto out : t.outputs) {
        std::cout << "Amount: " << out.amt << ". PubKey Hash: " << out.pub_hash << std::endl;
    }
    std::cout << std::endl;
}

// void print_transaction(transaction* t) {
//     std::cout << "Sender: " << t->sender_address << std::endl;
//     std::cout << "Receiver: " << t->receiver_address << std::endl;
//     std::cout << "Amount: " << t->amount << std::endl;
//     std::cout << "Transaction Fee: " << t->transaction_fee << std::endl;
//     std::cout << "Signature: " << t->script_sig << std::endl;
//     std::cout << "PubKey Verification: " << t->script_pub_key << std::endl;

//     std::cout << std::endl;

//     return;
// }

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
