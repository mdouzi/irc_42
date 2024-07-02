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
  std::cout << "Handling Client Commands" << std::endl;
  std::cout << "The input size is " << this->input.size() << std::endl;
  std::cout << "The input is " << this->input[0] << std::endl;
  if (this->input.size() > 0){
    if (this->input[0] == "CAP" || this->input[0] == "cap") {
      hexchat((*this), index);
      std::cout << "HEXCHAT CONNECTED" << std::endl;
    }
    if(this->input[0] == "PASS" || this->input[0] == "pass") {
      if (this->clients[index].getAuth() == true) {
        send_reply(cfd, "PASS : ERR_ALREADYREGISTRED :You may not reregister 11");
      } else {
        pass((*this), index);
      }
    }
    if(this->input[0] == "USER" || this->input[0] == "user") {
      if(this->clients[index].getAuth() == true) {
          if(this->clients[index].getReg() == true) {
            send_reply(cfd, "PASS : ERR_ALREADYREGISTRED :You may not reregister 11");
          } else {
            this->clients[index].setReg(true);
            user((*this), index);
          }
      }
      else {
        send_reply(cfd, "USER : ERR_NOTREGISTERED :You have not registered");
      }
    }
    if (this->input[0] == "NICK" || this->input[0] == "nick") {
      if(this->clients[index].getAuth() == true) {
          nick((*this), index);
      } else {
        send_reply(cfd, "NICK : ERR_ALREADYREGISTRED :You may not reregister");
      }
    }
    if (this->input[0] == "JOIN" || this->input[0] == "join") {
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
    if (this->input[0] == "PRIVMSG" || this->input[0] == "privmsg") {
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
    if (this->input[0] == "MODE" || this->input[0] == "mode") {
      if (this->clients[index].getAuth() == true) {
        if (this->clients[index].getReg2() == true) {
          mode((*this), index);
        } else {
          send_reply(cfd, "MODE : ERR_NOTREGISTERED :You may not registered");
        }
      } else {
        send_reply(cfd, "MODE : ERR_NOTREGISTERED :You have not registered");
      }
    }
    else if (this->input[0] == "KICK" || this->input[0] == "kick")
    {
      std::string user;
      std::string Xchannel;
    }
  }
}

void my_server::SplitInput(char buffer[255], std::vector<std::string> &tokens) {
    std::stringstream ss(buffer);
    std::string token;
    int i = 0;
    while (ss >> token) {
      std::cout << "token index is " << i << " and the token is >>  " << token << std::endl;
      tokens.push_back(token);
      i++;
    }
}

// set password
void my_server::setPassword(std::string const & password) {
    this->_password = password;
}

// get password
std::string const & my_server::getPassword() const {
    return this->_password;
}


bool my_server::findChannel(std::string const &ChannelName) 
{
  for(std::vector<Channel>::iterator it = channels.begin(); it != channels.end() ; it++)
  {
    if(it->getName() == ChannelName)
        return true;
  }
  return false;
}


bool my_server::isUserOnChannel(std::string const &ChannelName, std::string const &ClientName)
{
  Channel find;
  for(std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); it++)
  {
    if(it->getName() == ChannelName)
    {
        find = (*it);
        break;
    }
  }
  if(find.isMember(ClientName) == true)
      return true;
  return false;
}


// std::vector<std::string> my_server::parseKickCommand(std::string const & message)
// {
//     std::vector<std::string> args;
//     std::istringstream iss(message);
//     std::string token;

//     // Skip the "KICK" command itself
//     iss >> token;

//     // Get the channel name
//     if (iss >> token)
//     {
//       if(token[0] == '#')
//           token.substr(1);
//     }
//     args.push_back(token);

//     // Get the user to be kicked
//     if (iss >> token)
//         args.push_back(token);

//     // Get the reason (which may contain spaces)
//     std::string reason;
//     if (std::getline(iss, reason))
//     {
//         // Remove leading whitespace (including the space before the colon)
//         size_t start = reason.find_first_not_of(" \t");
//         if (start != std::string::npos)
//             reason = reason.substr(start);

//         // Remove the leading colon if present
//         if (!reason.empty() && reason[0] == ':')
//             reason = reason.substr(1);

//         if (!reason.empty())
//             args.push_back(reason);
//     }

//     return args;
// }

