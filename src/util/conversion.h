
#ifndef UTIL_CONVERSION_H
#define UTIL_CONVERSION_H

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "types/all.h"

std::string bytes_to_hex(const std::vector<uint8_t>& bytes);

std::string to_hex(const unsigned char* data, size_t len);

std::vector<unsigned char> hex_to_bin(const std::string& hex);

std::vector<uint8_t> uint64_to_bytes(uint64_t value);

std::vector<uint8_t> serialize(const tx& tx);
std::vector<uint8_t> serialize(block& b);

std::vector<uint8_t> serialize(net_msg msg);
net_msg deserialize_msg_header(std::vector<uint8_t> msg);

#endif