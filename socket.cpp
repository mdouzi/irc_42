#include "socket.hpp"
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int createSocket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket error" << std::endl;
        exit(2);
    }
    return sockfd;
}

void setSocketOptions(int sockfd) {
    int en = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en));
}

void bindSocket(int sockfd, sockaddr_in &addr, uint16_t port) {
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (bind(sockfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Bind error" << std::endl;
        exit(2);
    }
}

void startListening(int sockfd) {
    if (listen(sockfd, 10) < 0) {
        std::cerr << "Listen error" << std::endl;
        exit(2);
    }
}

void setNonBlocking(int fd) {
    fcntl(fd, F_SETFL, O_NONBLOCK);
}

int acceptClient(int sockfd) {
    int client_fd = accept(sockfd, NULL, NULL);
    if (client_fd < 0) {
        std::cerr << "Accept error" << std::endl;
        exit(2);
    }
    setNonBlocking(client_fd);
    return client_fd;
}
