#include "server.h"

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <thread>

#include "constants.h"
#include "types/all.h"

;

// void server_message_receive_loop(int client_sock_fd) {
//     std::vector<uint8_t> buffer;
//     char temp_buffer[1024];
//     ssize_t bytes_received;

//     while (true) {
//         bytes_received = recv(client_sock_fd, temp_buffer, sizeof(temp_buffer), 0);
//         if (bytes_received <= 0) {
//             std::cerr << "Connection closed or error occurred" << std::endl;
//             close(client_sock_fd);
//             break;
//         }

//         // Append received data to buffer
//         buffer.insert(buffer.end(), temp_buffer, temp_buffer + bytes_received);

//         while (buffer.size() >= sizeof(uint32_t)) {
//             // Check if we have the length of the message
//             uint32_t message_length = ntohl(*reinterpret_cast<uint32_t*>(buffer.data()));
//             if (buffer.size() >= message_length) {
//                 // Message msg;
//                 msg m;
//                 m.length = message_length;
//                 m.type = ntohs(*(reinterpret_cast<uint16_t*>(buffer[sizeof(uint32_t)])));

//                 m.payload.assign(buffer.begin() + sizeof(uint32_t) + sizeof(uint16_t), buffer.begin() + message_length);
//                 // msg.length = message_length;
//                 // msg.type = ntohs(*reinterpret_cast<uint16_t*>(&buffer[sizeof(uint32_t)]));
//                 // msg.payload.assign(buffer.begin() + sizeof(uint32_t) + sizeof(uint16_t), buffer.begin() + message_length);

//                 // Process the message
//                 if (m.type == 1) {
//                     std::cout << "Received request" << std::endl;
//                 } else if (m.type == 2) {
//                     std::cout << "Received response" << std::endl;
//                 }

//                 // Remove processed message from buffer
//                 buffer.erase(buffer.begin(), buffer.begin() + message_length);
//             } else {
//                 // We don't have a complete message yet
//                 break;
//             }
//         }
//     }
// }

// // start listening server given node with listen addr
// int start_node_server(full_node& node) {
//     int server_sock;
//     sockaddr_in server_addr;
//     int port = TESTNET_LISTEN_PORT;

//     if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
//         return -1;
//     }

//     int opt = 1;
//     if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) return -1;

//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = INADDR_ANY;
//     server_addr.sin_port = (htons(port));
//     memset(&(server_addr.sin_zero), '\0', 8);

//     if (bind(server_sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) return -1;

//     if (listen(server_sock, 5) == -1) return -1;

//     std::cout << "Server listening on port " << port << std::endl;
//     handle_server_accept_loop(node, server_sock);
// }

// void handle_server_accept_loop(full_node& node, int sock_fd) {
//     sockaddr_in client_addr;
//     socklen_t caddr_size = sizeof(client_addr);
//     for (; true;) {
//         int client_sock = accept(sock_fd, (sockaddr*)&client_addr, &caddr_size);
//         if (client_sock == -1) {
//             std::cerr << "Accept failed. Error: " << strerror(errno) << std::endl;
//             continue;
//         }

//         std::cout << "Got connection from "
//                   << inet_ntoa(client_addr.sin_addr) << ":"
//                   << ntohs(client_addr.sin_port) << std::endl;

//         server_message_receive_loop(client_sock);
//     }
// }

// // PROTOCOL LEVEL
// void server_message_received_loop(int client_sock_fd) {
//     for (; true;) {
//         u_char* buffer[1024];
//         std::memset(buffer, 0, sizeof(buffer));
//         int num_bytes_recvd = recv(client_sock_fd, buffer, sizeof(buffer) - 1, 0);

//         std::string msg = std::string(reinterpret_cast<const char*>(buffer), sizeof(buffer));

//         std::cout << "Message: " << msg << std::endl;

//         if (num_bytes_recvd > 0) {
//             std::string msg = "Received message.\n";
//             send(client_sock_fd, &msg, sizeof(msg), 0);
//         } else {
//             send(client_sock_fd, "shit", 4, 0);
//         }
//     }
// }
