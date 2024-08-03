#include "wallet.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "core/all.h"
#include "crypto/all.h"
#include "util/all.h"

// s_addr is coinbase/magicmoneycenter
// inputs from MMC
// TODO: add security checks, ie: num_inputs = inputs.size()?
tx gen_gns_tx(wallet& w, std::string r_addr, std::string r_pub_key, uint64_t amt) {
    std::string s_addr = "magicmoneycenter";
    std::vector<tx_in> inputs{};

    // create public hash for receiver by double hashing
    std::vector<uint8_t> pub_key_bytes(r_pub_key.begin(), r_pub_key.end());
    std::string pub_hash = bytes_to_hex(hash_sha256(hash_sha256(pub_key_bytes)));
    tx_out output{amt, pub_hash};
    std::vector<tx_out> outputs{output};

    tx gns_tx = init_tx(s_addr, r_addr, 0, 1, inputs, outputs);

    // NOTE - Hardcoded holder fn until created syncing
    // TODO - move to wallet_sync when created
    //  add token to pool.
    std::string tx_hash = hash_tx(gns_tx);
    uint32_t output_idx = 0;
    add_utxo_to_w_pool(w, tx_hash, output_idx, amt);

    return gns_tx;
}

// add error codes eventually 😭
tx create_tx(wallet& w, const std::string& r_addr, std::string r_pub, const uint64_t& amt) {
    tx result;

    // TODO: incorporate tx fees into amt
    // check if have enough sums, return if not.
    if (get_balance(w.pool) < amt) {
        return result;
    }

    // TODO: hard and soft refreshes for utxo pool
    // FIXME: not stable or backed up, once fn starts,
    // tokens could be lost; will have to refresh
    // could do acid compliant: copy list and work on copy. when transaction is sent, update real
    // impl: pass wallet by value and update after

    // go through utxo pool and sum up tokens until enough.
    // add to inputs list
    uint64_t sum = 0;
    std::vector<tx_in> inputs;
    while (sum < amt) {
        // get current node
        w_utxo cur = w.pool.front();
        sum += cur.amt;

        // add to inputs
        tx_in in = tx_in{cur.tx_hash, cur.sig, cur.output_idx};
        inputs.push_back(in);

        w.pool.pop_front();
    }

    // create necessary outputs
    // calculate pub_hash for receiver (double hashed r pub)
    std::vector<uint8_t> r_pub_key_bytes(r_pub.begin(), r_pub.end());
    std::string r_pub_hash = bytes_to_hex(hash_sha256(hash_sha256(r_pub_key_bytes)));
    tx_out main_out = tx_out{amt, r_pub_hash};

    // create output for return utxo to sender
    std::vector<uint8_t> w_p_addr_bytes(w.pub_key.begin(), w.pub_key.end());
    std::string w_pub_hash = bytes_to_hex(hash_sha256(hash_sha256(w_p_addr_bytes)));
    tx_out ret_out = tx_out{sum - amt, w_pub_hash};

    std::vector<tx_out> outputs{main_out, ret_out};

    // put everything together in tx
    result.s_addr = w.addr;
    result.r_addr = r_addr;
    result.inputs = inputs;
    result.outputs = outputs;

    return result;

    // TODO: send to node for addition to block
}

// FIXME -  can easily add faulty utxos to pool
void add_utxo_to_w_pool(wallet& w, const std::string& tx_hash, const uint32_t& output_idx, const uint64_t& amt) {
    // add signature + pubk = sig
    // signature = priv key signed on tx_hash
    // + pub key

    std::vector<uint8_t> tx_hash_bytes(tx_hash.begin(), tx_hash.end());
    std::vector<uint8_t> hash_sig_bytes = sign_tx(tx_hash_bytes, w.priv_key);
    std::string sig = bytes_to_hex(hash_sig_bytes) + " " + w.pub_key;

    w_utxo utxo{tx_hash, output_idx, amt, sig};

    // most recent utxos first, so add to back
    w.pool.push_back(utxo);

    // std::cout << get_balance(w.pool) << std::endl;

    return;
}

wallet init_wallet() {
    crypto_keys keys = gen_keys();
    std::string wallet_address = gen_wallet_addr(keys.pub_key);

    return wallet(keys.pub_key, keys.priv_key, wallet_address);
}

/*
    HELPER FUNCTIONS
*/

uint64_t get_balance(std::list<w_utxo> pool) {
    uint64_t sum = 0;
    if (pool.empty()) {
        return sum;
    }

    for (w_utxo i : pool) {
        sum += i.amt;
    }
    return sum;
}