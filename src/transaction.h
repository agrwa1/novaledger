#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// input, output, signature, metadata
// sender, receiver, amount, signature, transaction_fee
//* implementing UTXO later
struct transaction {
    std::string sender_address;
    std::string receiver_address;
    int64_t amount;
    int64_t transaction_fee;
    std::string signature;
};

#endif