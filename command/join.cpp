#include "command.hpp"

void join(my_server& server, int index) {
    bool found = false;
    int idx = 0;
    std::string key;

    if (server.input.size() < 2) {
        server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_NEEDMOREPARAMS :Not enough parameters");
        return;
    }

    std::string channelName = server.input[1];
    if (server.input.size() == 3) {
         key = server.input[2];
    }
    if (channelName[0] == '#') {
        for (size_t i = 0; i < server.channels.size(); ++i) { 
            if (server.channels[i].getName() == channelName) {
                found = true;
                idx = i;
                break;
            }
        }

        if (found) {
            if (server.channels[idx].isHavePassword() ) {
                if (server.channels[idx].getPassword() != key) {
                    server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_BADCHANNELKEY :Cannot join channel because of wrong password");
                    return;
                } else {
                        if (server.channels[idx].getPassword() == key) {
                            server.channels[idx].addClientToChannel(server.clients[index]);
                    }
                }
            } else if (server.channels[idx].isInviteOn() && !server.channels[idx].isInvited(server.clients[index])) {
                server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_INVITEONLYCHAN :Cannot join channel because it is invite only");
                return;
            } else if (server.channels[idx].getLimit() != 0 && server.channels[idx].getLimit() <= server.channels[idx].getUsers().size()) {
                server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_CHANNELISFULL :Cannot join channel because it is full");
                return;
            } else {
                server.channels[idx].addClientToChannel(server.clients[index]);
            }

            std::string joinMessage = ":" + server.clients[index].getNickName() + "!" + server.clients[index].getUserName() + " JOIN " + channelName;
            for (size_t i = 0; i < server.channels[idx].getUsers().size(); ++i) {
                server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), joinMessage);
            }

            for (size_t i = 0; i < server.channels[idx].getUsers().size(); ++i) {
                std::string namesList = ":fullhaha.irc.com 353 " + server.channels[idx].getUsers()[i].getNickName() + " = " + channelName + " :";
                for (size_t j = 0; j < server.channels[idx].getUsers().size(); ++j) {
                    if (j > 0) namesList += " ";
                    if (server.channels[idx].isOperator(server.channels[idx].getUsers()[j])) {
                        namesList += "@";
                    }
                    namesList += server.channels[idx].getUsers()[j].getNickName();
                }
                server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), namesList);

                std::string endNames = ":fullhaha.irc.com 366 " + server.channels[idx].getUsers()[i].getNickName() + " " + channelName + " :End of /NAMES list.";
                server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), endNames);
            }

        } else {
            server.channels.push_back(Channel(channelName, "")); 
            idx = server.channels.size() - 1;
            server.channels[idx].addClientToChannel(server.clients[index]);
            server.channels[idx].setName(channelName);
            server.channels[idx].addOperator(server.clients[index].getNickName());

            std::string channelinfo = ":" + server.clients[index].getNickName() + "!" + server.clients[index].getUserName() + " JOIN " + channelName;
            server.send_reply(server.clients[index].getClientFd(), channelinfo);

            std::string namesList = ":fullhaha.irc.com 353 " + server.clients[index].getNickName() + " = " + channelName + " :@" + server.clients[index].getNickName();
            server.send_reply(server.clients[index].getClientFd(), namesList);

            std::string endNames = ":fullhaha.irc.com 366 " + server.clients[index].getNickName() + " " + channelName + " :End of /NAMES list.";
            server.send_reply(server.clients[index].getClientFd(), endNames);
        }
    } else {
        server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_NOSUCHCHANNEL :No such channel");
    }
}

