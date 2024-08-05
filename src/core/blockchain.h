#ifndef CORE_BLOCKCHAIN_H
#define CORE_BLOCKCHAIN_H

#include "types/all.h"

block mine_new_block(blockchain& chain);

void add_tx_to_blkchn_pool(blockchain& chain, tx_vec txs);

void add_tx_to_blkchn_pool(blockchain& chain, tx t);

#endif