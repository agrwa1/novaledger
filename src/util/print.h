#ifndef UTIL_PRINT_H
#define UTIL_PRINT_H

#include "types/all.h"

void print_tx(tx t);
void print_wallet(wallet w);
void print_block(block b);
void print_blockchain(const blockchain& b);
void print_utxo_key(utxo_key key);
void print_utxo_val(utxo_val val);
void print_utxo_set(utxo_set& pool);

#endif