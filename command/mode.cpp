#include "command.hpp"

void mode(my_server& server, int index) {
    if (server.input.size() <= 2) {
        server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_NEEDMOREPARAMS :Not enough parameters");
        return;
    } else if (server.input.size() == 3 || server.input.size() == 4) {

        std::string channelName = server.input[1];
        std::string mode = server.input[2];
        std::string argOfTheMode = server.input[3];

        bool found = false;
        int idx = 0;

        for (size_t i = 0; i < server.channels.size(); ++i) {
            if (server.channels[i].getName() == channelName) {
                found = true;
                idx = i;
                break;
            }
        }
        if (found) {
            server.channels[idx].setMode(mode);
            server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
            std::cout << "Channel name: " << server.channels[idx].getName() << std::endl;
            std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
        } else {
            server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_NOSUCHCHANNEL :No such channel");
        }
    }
    else {
        server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_NEEDMOREPARAMS :Not enough parameters");
    }
}