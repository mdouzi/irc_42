#include "command.hpp"

void join(my_server& server, int index) {
    
    bool found = false;
    int idx = 0;

    if (server.input.size() < 2) {
        server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_NEEDMOREPARAMS :Not enough parameters");
        return;
    } else if (server.input.size() == 2) {
        std::string channelName = server.input[1];
        if (channelName[0] == '#') {
            for (size_t i = 0; i < server.channels.size(); ++i) {
                if (server.channels[i].getName() == channelName) {
                    found = true;
                    idx = i;
                    break;
                }
            }
            if (found) {
                server.channels[idx].addClientToChannel(server.clients[index]);
                std::cout << server.channels[idx].getName() << std::endl;
                server.send_reply(server.clients[index].getClientFd(), "JOIN :You have joined the channel");
                std::cout << "Channel name: " << server.channels[idx].getName() << std::endl;
                std::cout << "Client " << server.clients[index].getNickName() << " joined channel " << server.channels[idx].getName() << std::endl;
            }
            else {
                server.channels.push_back(Channel(channelName, ""));
                server.channels[server.channels.size() - 1].addClientToChannel(server.clients[index]);
                server.channels[server.channels.size() - 1].setName(channelName);
                server.send_reply(server.clients[index].getClientFd(), "JOIN :You have joined the channel");
                std::cout << "Channel name: " << server.channels[idx].getName() << std::endl;
                std::cout << "Client " << server.clients[index].getNickName() << " joined channel " << server.channels[idx].getName() << std::endl;
            }
        } else {
                server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_NOSUCHCHANNEL :No such channel");
        }
    }
}