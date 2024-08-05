#include "utxo.h"

#include <iostream>
#include <string>

#include "crypto/all.h"
#include "types/all.h"
#include "util/all.h"

bool update_utxo_set_from_block(utxo_set& pool, block& blk) {
    /*
            Pseudocode:
            for each tx:
                validate tx:
                    for each input
                        inputs exist and are unspent in pool
                        sig unlocks lock script
                    ** validate that tx follows consensus rules, tx fees ...

            for each tx:
                remove necessary inputs
                add all outputs
    */

    // validation loop
    for (int i = 0; i < blk.txs.size(); i++) {
        tx t = blk.txs[i];

        // TODO: add support for coinbase txs
        // validate inputs: make sure tx input is not bs
        for (auto in : t.inputs) {
            utxo_key key = utxo_key_from_input(in);
            print_utxo_key(key);

            // get back after finished adding utxo to set
            if (!utxo_is_valid(pool, key, in)) {
                std::cout << "UTXO is Invalid." << std::endl;
                return false;
            }
        }
    }

    // if returs false before update loop, abort block

    // update loop
    for (int i = 0; i < blk.txs.size(); i++) {
        tx t = blk.txs[i];
        // print_tx(t);

        // remove inputs
        for (auto in : t.inputs) {
            utxo_key key = utxo_key_from_input(in);
            remove_utxo(pool, key);
        }

        // add outputs,
        // index on i,
        // take tx hash from t + index => utxo key.
        // use output as utxo val
        for (uint32_t i = 0; i < t.outputs.size(); i++) {
            tx_out out = t.outputs[i];

            utxo_key key = utxo_key{hash_tx(t), i};
            utxo_val val = utxo_val{out.amt, out.tx_pub_hash};

            add_utxo(pool, key, val);
        }
    }

    return true;
}

bool utxo_exists_in_pool(utxo_set& pool, utxo_key& key) {
    return (pool.find(key) != pool.end());
}

bool utxo_is_valid(utxo_set& pool, utxo_key& key, tx_in in) {
    if (!utxo_exists_in_pool(pool, key)) return false;
    // sig = "signature" "public key"
    // pub_hash = hash(hash(public key))

    // splitting sig into parts
    // std::string signature, pub_key;
    // make this not shit itself
    size_t space_idx = key.prev_tx_hash.find(' ');
    if (space_idx == std::string::npos) {
        return false;
    }
    std::string signature = key.prev_tx_hash.substr(0, space_idx);
    std::string pub_key = key.prev_tx_hash.substr(space_idx);

    std::cout << "Signature: \"" << signature << "\"" << std::endl;
    std::cout << "Public Key: \"" << pub_key << "\"" << std::endl;

    return true;
}

void remove_utxo(utxo_set& pool, utxo_key key) {
    if (utxo_exists_in_pool(pool, key)) {
        std::cout << "Removing UTXO: \n\t";
        print_utxo_key(key);
        pool.erase(key);
    }
}

void add_utxo(utxo_set& pool, utxo_key key, utxo_val val) {
    // std::cout << "Adding UTXO to pool: \n\t\"" << key.prev_tx_hash << "\" ["
    //           << key.output_idx << "] => " << val.amt << std::endl
    //           << "\tPubKey Hash: " << val.tx_pub_hash << std::endl;
    pool[key] = val;
}

utxo_key utxo_key_from_input(tx_in in) {
    return utxo_key{in.tx_hash, in.output_idx};
}