#include "command.hpp"
#include "../client.hpp"
void send_reply_nick(int cfd, std::string const & message)
{
   std::string reply = message + "\r\n";
  ssize_t bytes_sent = send(cfd, reply.c_str(), reply.length(), 0);
  if (bytes_sent == -1) {  
    std::cerr << "Error sending reply: " << strerror(errno) << std::endl;
  }
}



void nick(my_server& server , int index) {
    server.clients[index].setNickName(server.input[1]);
    send_reply_nick(server.clients[index].getClientFd(), "----> NICK COMMAND SUCCESSFUL <----");  
}
