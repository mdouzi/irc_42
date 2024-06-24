#include "client.hpp"
#include "server.hpp"


bool InThechannel(my_server const &server, std::string const &name)
{
  for(std::vector<client>::iterator it = server.clients.begin(); it != server.clients.end(); it++) 
  {
    if(it->getNickName() == name)
        return true;
  }
  return false;
}


