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

bool isUniqueNickName(const std::string &Nick, my_server &server)
{
  for(std::vector<client>::iterator it = server.clients.begin(); it != server.clients.end(); it++)
  {
    if(it->getNickName() == Nick)
          return false;
  }
  return true;
}


bool isValidNickName(const std::string& nick)
{
  if(nick.empty() || nick.length() > 9)
      return false;
  if (!isalpha(nick[0]) && nick[0] != '[' && nick[0] != ']' && nick[0] != '\\' && nick[0] != '`' && nick[0] != '_' && nick[0] != '^' && nick[0] != '{' && nick[0] != '|' && nick[0] != '}') 
    return false;
  
  for (size_t i = 1; i < nick.length(); ++i)
  {
        char c = nick[i];
        if (!isalnum(c) && c != '-' && c != '[' && c != ']' && c != '\\' && c != '`' && c != '_' && c != '^' && c != '{' && c != '|' && c != '}')
            return false;
  }

  return true;
}


void nick(my_server& server , int index) {
    if(!isUniqueNickName(server.input[1], server))
    {
      server.clients[index].setReg2(false);
      send_reply_nick(server.clients[index].getClientFd(), "NICK : ERR_NICKNAMEINUSE (433) : Nickname is already in use");
      return;
    }
    else if (!isValidNickName(server.input[1])) {
      server.clients[index].setReg2(false);
      send_reply_nick(server.clients[index].getClientFd(), "NICK : ERR_ERRONEUSNICKNAME (432) : Erroneous nickname");
      return;
    }
    else {
      server.clients[index].setNickName(server.input[1]);
      send_reply_nick(server.clients[index].getClientFd(), "----> NICK COMMAND SUCCESSFUL <----");  
      server.clients[index].setReg2(true);
    }
}


