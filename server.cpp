#include "server.hpp"
#include "socket.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "./command/command.hpp"
#include <sstream>
#include <string>
#include "client.hpp"


my_server::my_server() {};
my_server::~my_server() {};
void my_server::runServer(wint_t port) {
    char buff[255];
    int sockfd = createSocket();
    sockaddr_in addr;
    pollfd pol;
    pol.events = POLLIN;
    pol.fd = sockfd;
    setSocketOptions(sockfd);
    bindSocket(sockfd, addr, port);
    startListening(sockfd);
    setNonBlocking(sockfd);
    this->_mypolls.push_back(pol);
    memset(buff, 0, sizeof(buff));
    while (true) {
        int poll_ret = poll(this->_mypolls.data(), this->_mypolls.size(), -1);
        if (poll_ret < 0) {
            std::cerr << "Poll error" << std::endl;
            exit(2);
        }
        for (size_t i = 0; i < this->_mypolls.size(); ++i) {
            if ((this->_mypolls[i].revents & POLLIN) != 1) {
                continue;
            }
            if ((this->_mypolls[i].fd == sockfd) & POLLIN) {
                int client_fd = acceptClient(sockfd);
                std::cout << "Client " << client_fd << " Connected " << std::endl;
                send_reply(client_fd, "->  Connected  <-");
                pollfd client_poll;
                client_poll.events = POLLIN;
                client_poll.fd = client_fd; 
                this->_mypolls.push_back(client_poll);
                client firstClient;
                firstClient.setClientFd(client_fd);
                clients.push_back(firstClient);
            } else {
                int ret = recv(this->_mypolls[i].fd, buff, 255, 0);
                if (ret <= 0) {
                    if (!this->_disconnectedClients[this->_mypolls[i].fd]) {
                        std::cout << "The Client " << this->_mypolls[i].fd << " Disconnected!!" << std::endl;
                        this->_disconnectedClients[this->_mypolls[i].fd] = true;
                    }
                }
                if (ret > 0) {
                    buff[ret] = '\0';
                    SplitInput(buff, this->input);
                    std::cout << "Polling " << this->_mypolls[i].fd << std::endl;
                    handleClientCommands(this->_mypolls[i].fd, (i - 1));
                    this->input.clear();
                    std::cout << buff;
                    memset(buff, 0, 255);
                }
            }
        }
    }
}


void my_server::send_reply(int cfd, std::string const & message) {
   std::string reply = message + "\r\n";
  ssize_t bytes_sent = send(cfd, reply.c_str(), reply.length(), 0);
  if (bytes_sent == -1) {  
    std::cerr << "Error sending reply: " << strerror(errno) << std::endl;
  }
}

void my_server::handleClientCommands(int cfd, int index)
{
  if(this->input[0] == "PASS") {
    if (this->clients[index].getAuth() == true) {
      send_reply(cfd, "PASS : ERR_ALREADYREGISTRED :You may not reregister");
    } else {
      pass((*this), index);
    }
  }
  else if(this->input[0] == "USER") {
    if(this->clients[index].getAuth() == true) {
        if(this->clients[index].getReg() == true) {
          send_reply(cfd, "PASS : ERR_ALREADYREGISTRED :You may not reregister");
        } else {
          this->clients[index].setReg(true);
          user((*this), index);
        }
    }
    else {
      send_reply(cfd, "USER : ERR_NOTREGISTERED :You have not registered");
    }
  }
  else if (this->input[0] == "NICK") {
    if(this->clients[index].getAuth() == true) {
      if(this->clients[index].getReg2() == true) {
        send_reply(cfd, "NICK : ERR_ALREADYREGISTRED :You may not reregister");
      } else {
        nick((*this), index);
        this->clients[index].setReg2(true);
      }
    } else {
      send_reply(cfd, "NICK : ERR_ALREADYREGISTRED :You may not reregister");
    }
  }
  else if (this->input[0] == "JOIN") {
    if(this->clients[index].getAuth() == true) {
      if(this->clients[index].getReg2() == true) {
        join((*this), index);
      } else {
        send_reply(cfd, "JOIN : ERR_NOTREGISTERED :You may not registered");
      }
    } else {
      send_reply(cfd, "JOIN : ERR_NOTREGISTERED :You have not registered");
    }
  }
  else if (this->input[0] == "PRIVMSG") {
    if (this->clients[index].getAuth() == true) {
      if (this->clients[index].getReg2() == true) {
        privmsg((*this), index);
      } else {
        send_reply(cfd, "PRIVMSG : ERR_NOTREGISTERED :You may not registered");
      }
    } else {
      send_reply(cfd, "PRIVMSG : ERR_NOTREGISTERED :You have not registered");
    }
  }
}

void my_server::SplitInput(char buffer[255], std::vector<std::string> &tokens) {
    std::stringstream ss(buffer);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
}
