
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "types/all.h"

std::string bytes_to_hex(const std::vector<uint8_t>& bytes) {
    std::stringstream ss;
    for (auto byte : bytes) {
        ss << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
    }
    return ss.str();
}

std::string to_hex(const unsigned char* data, size_t len) {
    std::ostringstream oss;
    for (size_t i = 0; i < len; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
    }
    return oss.str();
}

std::vector<unsigned char> hex_to_bin(const std::string& hex) {
    // Check if the hex string length is even
    if (hex.length() % 2 != 0) {
        throw std::invalid_argument("Hexadecimal string length must be even.");
    }

    std::vector<unsigned char> binaryData;
    binaryData.reserve(hex.length() / 2);

    // Iterate through each pair of hex digits
    for (size_t i = 0; i < hex.length(); i += 2) {
        // Extract two characters (one byte) from the string
        std::string byteString = hex.substr(i, 2);
        unsigned char byteValue = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16));
        binaryData.push_back(byteValue);
    }

    return binaryData;
}

std::vector<uint8_t> uint64_to_bytes(uint64_t value) {
    std::vector<uint8_t> bytes(8);
    std::memcpy(bytes.data(), &value, 8);
    return bytes;
}

/*
    SERIALIZATIONS
*/

void serialize(std::vector<uint8_t>& buffer, const std::vector<uint8_t>& vec) {
    buffer.insert(buffer.end(), vec.begin(), vec.end());
}

void serialize(std::vector<uint8_t>& buffer, const std::string& str) {
    buffer.insert(buffer.end(), str.begin(), str.end());
}

void serialize(std::vector<uint8_t>& buffer, uint8_t value) {
    buffer.push_back((value >> 0) & 0xFF);
    buffer.push_back((value >> 8) & 0xFF);
    buffer.push_back((value >> 16) & 0xFF);
    buffer.push_back((value >> 24) & 0xFF);
}

void serialize(std::vector<uint8_t>& buffer, uint32_t value) {
    buffer.push_back((value >> 0) & 0xFF);
    buffer.push_back((value >> 8) & 0xFF);
    buffer.push_back((value >> 16) & 0xFF);
    buffer.push_back((value >> 24) & 0xFF);
}

void serialize(std::vector<uint8_t>& buffer, uint64_t value) {
    buffer.push_back((value >> 0) & 0xFF);
    buffer.push_back((value >> 8) & 0xFF);
    buffer.push_back((value >> 16) & 0xFF);
    buffer.push_back((value >> 24) & 0xFF);
}

void serialize(std::vector<uint8_t>& buffer, const tx_in& input) {
    serialize(buffer, input.tx_hash);
    serialize(buffer, input.sig);
    serialize(buffer, input.output_idx);
    serialize(buffer, input.seq_num);
}

void serialize(std::vector<uint8_t>& buffer, const tx_out& output) {
    // Convert the amount to a byte array (64-bit)
    buffer.push_back((output.amt >> 0) & 0xFF);
    buffer.push_back((output.amt >> 8) & 0xFF);
    buffer.push_back((output.amt >> 16) & 0xFF);
    buffer.push_back((output.amt >> 24) & 0xFF);
    buffer.push_back((output.amt >> 32) & 0xFF);
    buffer.push_back((output.amt >> 40) & 0xFF);
    buffer.push_back((output.amt >> 48) & 0xFF);
    buffer.push_back((output.amt >> 56) & 0xFF);

    serialize(buffer, output.tx_pub_hash);
}

void serialize(std::vector<uint8_t>& buffer, time_t value) {
    for (size_t i = 0; i < sizeof(time_t); ++i) {
        buffer.push_back((value >> (i * 8)) & 0xFF);
    }
}

// NOTE - PURPOSEFULLY NOT SERIALIZING INPUTS OR OUTPUTS FIELDS; PLAN TO REMOVE THEM
std::vector<uint8_t> serialize(const tx& tx) {
    std::vector<uint8_t> buffer;

    // Serialize version
    serialize(buffer, tx.version);

    // Serialize inputs
    serialize(buffer, tx.num_input);
    for (const auto& input : tx.inputs) {
        serialize(buffer, input);
    }

    // Serialize outputs
    serialize(buffer, tx.num_output);
    for (const auto& output : tx.outputs) {
        serialize(buffer, output);
    }

    return buffer;
}

/*
    FIELDS:
        - CONSTANT: timestamp, version, difficulty
        - PROVIDED: height, prev_hash, txs
        - CALCULATED: merkle_root, nonce
*/
// TODO: make sure structure is valid
std::vector<uint8_t> serialize(block& b) {
    std::vector<uint8_t> buffer;

    serialize(buffer, b.timestamp);
    serialize(buffer, b.version);
    serialize(buffer, b.difficulty);

    serialize(buffer, b.height);
    serialize(buffer, b.prev_hash);
    for (auto t : b.txs) {
        std::vector<uint8_t> bytes = serialize(t);
        for (auto by : bytes) {
            buffer.push_back(by);
        }
    }

    serialize(buffer, b.merkle_root);
    serialize(buffer, b.nonce);

    return buffer;
}
