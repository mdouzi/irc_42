#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <netinet/in.h>
#include <vector>
#include <poll.h>

int createSocket();
void setSocketOptions(int sockfd);
void bindSocket(int sockfd, sockaddr_in &addr, uint16_t port);
void startListening(int sockfd);
void setNonBlocking(int fd);
int acceptClient(int sockfd);

#endif
