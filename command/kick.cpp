#include "client.hpp"
#include "server.hpp"

// std::vector<std::string> parseKickCommand(const std::string& message)
// {
//     std::vector<std::string> args;
//     std::istringstream iss(message);
//     std::string token;

//     // Skip the "KICK" command itself
//     iss >> token;

//     // Get the channel name
//     if (iss >> token)
//         args.push_back(token);

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
