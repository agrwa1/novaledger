#ifndef CMD_GENESIS_H
#define CMD_GENESIS_H

#include <vector>

#include "types/all.h"

full_node genesis(uint32_t num_wallets = 10, uint64_t amt = 5'000'000'000ULL);

wallet_vec gen_gns_wallets(uint32_t num_wallets);
tx_vec gen_gns_txs(wallet_vec wallets, uint64_t amt);
blockchain blockchain_gns(tx_vec& txs);

#endif