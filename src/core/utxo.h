#ifndef CORE_UTXO_H
#define CORE_UTXO_H

// update utxo_set from added block
// revert utxo_set from removed block

#include "types/all.h"

bool update_utxo_set_from_block(utxo_set& pool, block& blk);
void revert_utxo_set_from_block();

bool utxo_exists_in_pool(utxo_set& pool, utxo_key& key);
// validate_tx_inputs
// validate_tx
// how to validate coinbase txs?

#endif