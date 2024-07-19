#include "command.hpp"

void invite(my_server &server, int index) {
    if (server.input.size() < 3) {
        server.send_reply(server.clients[index].getClientFd(), "INVITE : ERR_NEEDMOREPARAMS :Not enough parameters");
        return;
    }

    std::string nickName = server.input[1];
    std::string channelName = server.input[2];
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
        if (server.channels[idx].isMember(server.clients[index].getNickName()) == false) {
            server.send_reply(server.clients[index].getClientFd(), "INVITE : ERR_NOTONCHANNEL :You're not on that channel");
            return;
        }
        else if (server.channels[idx].isOperator(server.clients[index]) == false) {
            server.send_reply(server.clients[index].getClientFd(), "INVITE : ERR_CHANOPRIVSNEEDED :You're not a channel operator");
            return;
        }
        else {
            for (size_t i = 0; i < server.clients.size(); ++i) {
                if (server.clients[i].getNickName() == nickName) {
                    // set the client as invited
                    server.channels[idx].setInvitedClients(server.clients[i]);
                    server.send_reply(server.clients[i].getClientFd(), ":" + server.clients[index].getNickName() + " INVITE " + nickName + " " + channelName);
                    server.send_reply(server.clients[index].getClientFd(), "INVITE :You have invited " + nickName + " to " + channelName);
                    return;
                }
            }
            server.send_reply(server.clients[index].getClientFd(), "INVITE : ERR_NOSUCHNICK :No such nick/channel");
        }
    } else {
        server.send_reply(server.clients[index].getClientFd(), "INVITE : ERR_NOSUCHCHANNEL :No such channel");
    }
}