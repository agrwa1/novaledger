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

bool utxo_exists_in_pool(utxo_set& pool, utxo_key& key);

bool utxo_is_valid(utxo_set& pool, utxo_key& key, tx_in in);

void remove_utxo(utxo_set& pool, utxo_key key);

void add_utxo(utxo_set& pool, utxo_key key, utxo_val val);

utxo_key utxo_key_from_input(tx_in in);

#endif