#include "client.hpp"
#include "server.hpp"


bool findChannel(my_server const &server, std::string const &namChannel) {
  
  for(std::vector<Channel>::iterator it = server.Channel.begin(); it != server.Channel.end(); it++)
  {
    if(it->getName() == nameChannel)
        return true;
  }
  return false;
} 

bool findUser(Channel const &server, std::string nameUser)
{
  std::vector<client> users;

  users = channel.getUsers();
  for(std::vector<client>::iterator it = users.begin(); it != users.end(); it++) 
  {
    if(it->getName() == nameUser)
        return true;
  }
  users.clear();
  return false;
}

std::vector<std::string> parseKickCommand(const std::string& message)
{
    std::vector<std::string> args;
    std::istringstream iss(message);
    std::string token;

    // Skip the "KICK" command itself
    iss >> token;

    // Get the channel name
    if (iss >> token)
        args.push_back(token);

    // Get the user to be kicked
    if (iss >> token)
        args.push_back(token);

    // Get the reason (which may contain spaces)
    std::string reason;
    if (std::getline(iss, reason))
    {
        // Remove leading whitespace (including the space before the colon)
        size_t start = reason.find_first_not_of(" \t");
        if (start != std::string::npos)
            reason = reason.substr(start);

        // Remove the leading colon if present
        if (!reason.empty() && reason[0] == ':')
            reason = reason.substr(1);

        if (!reason.empty())
            args.push_back(reason);
    }

    return args;
}

int getChannel(std::vector<Channel> const & channels, std::string const &ChannelName)
{
  int i = 0;
  while(channels[i])
  {
    if(channels[i].getName() == ChannelName)
        return i;
    i++;
  }
  return -1;
}

int getClient(std::vector<client> const &clients, std::string const &clientName)
{
  int i = 0;
  while(clients[i])
  {
    if(clients[i].getNickName() == clientName)
      return i;
    i++;
  }
  return -1;
}

void kick(my_server const &server, int index) 
{
  int i;
  std::string channelName;
  std::string userName;
  std::string reason;
  std::vector args = parseKickCommand(server.input);
  channelName = args[0];
  user = args[1];
  reason = args[2];


  if(!findChannel(server, channelName)) 
      return;
  if(!findUser(server, userName))
      return;
  else {
    i = getChannel(server.Channels, channelName);
    server.channels[i].deleteClientFromChannel(getClient(server.clients, userName));
    server.channels[i],broadcast("client hase been removed");
  }
}
