#include <arpa/inet.h>
#include <sys/socket.h>

#include <string>

#include "constants.h"

struct msg {
    uint32_t length;
    uint16_t type;
    std::string payload;
};

void client_send_message() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int port = TESTNET_LISTEN_PORT;

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr))) {
    }

    msg m;
    m.payload = "Hello World!";
    m.type = 1;
    m.length = sizeof(uint16_t) + sizeof(uint32_t) + 12;

    uint32_t total_len = sizeof(uint32_t) + sizeof(uint16_t) + m.payload.size();
    char* buffer = new char[total_len];

    uint32_t net_len = htonl(m.length);
    std::memcpy(buffer, &net_len, sizeof(uint32_t));

    uint16_t type_len = htons(m.type);
    std::memcpy(buffer + sizeof(uint32_t), &type_len, sizeof(uint16_t));

    std::memcpy(buffer + sizeof(uint32_t) + sizeof(uint16_t), m.payload.data(), m.payload.size());

    send(sockfd, buffer, total_len, 0);

    delete[] buffer;
}