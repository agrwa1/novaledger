#ifndef UTIL_PRINT_H
#define UTIL_PRINT_H

#include "wallet/all.h"

void print_tx(tx t);

void print_wallet(wallet w);

void print_block(block b);
void print_blockchain(const blockchain& b);

#endif