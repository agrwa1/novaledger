
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

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