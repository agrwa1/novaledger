#ifndef CORE_BLOCKCHAIN_H
#define CORE_BLOCKCHAIN_H

#include "types/all.h"

void mine_new_block(full_node* node);
void add_tx_to_blkchn_pool(blockchain& chain, tx t);
void add_txs_to_blkchn_pool(blockchain& chain, tx_vec txs);

#endif