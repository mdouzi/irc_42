#include "command.hpp"

void join(my_server& server, int index) {
    bool found = false;
    int idx = 0;

    if (server.input.size() < 2) {
        server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_NEEDMOREPARAMS :Not enough parameters");
        return;
    }

    std::string channelName = server.input[1];
    if (channelName[0] == '#') {
        // Check if the channel already exists
        for (size_t i = 0; i < server.channels.size(); ++i) {
            if (server.channels[i].getName() == channelName) {
                found = true;
                idx = i;
                break;
            }
        }

        if (found) {
            if (server.channels[idx].isInviteOn() && !server.channels[idx].isInvited(server.clients[index])) {
                server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_INVITEONLYCHAN :Cannot join channel because it is invite only");
                return;
            }
            if (server.channels[idx].getLimit() != 0 && server.channels[idx].getLimit() <= server.channels[idx].getUsers().size()) {
                server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_CHANNELISFULL :Cannot join channel because it is full");
                return;
            }
            server.channels[idx].addClientToChannel(server.clients[index]);

            // Notify all users in the channel about the new user
            std::string joinMessage = ":" + server.clients[index].getNickName() + "!" + server.clients[index].getUserName() + " JOIN " + channelName;
            for (size_t i = 0; i < server.channels[idx].getUsers().size(); ++i) {
                server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), joinMessage);
            }

            // Send names list to all clients in the channel
            for (size_t i = 0; i < server.channels[idx].getUsers().size(); ++i) {
                std::string namesList = ":zaba.org 353 " + server.channels[idx].getUsers()[i].getNickName() + " = " + channelName + " :";
                for (size_t j = 0; j < server.channels[idx].getUsers().size(); ++j) {
                    if (j > 0) namesList += " ";
                    if (server.channels[idx].isOperator(server.channels[idx].getUsers()[j])) {
                        namesList += "@";
                    }
                    namesList += server.channels[idx].getUsers()[j].getNickName();
                }
                server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), namesList);

                // Send end of names list to the client
                std::string endNames = ":zaba.org 366 " + server.channels[idx].getUsers()[i].getNickName() + " " + channelName + " :End of /NAMES list.";
                server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), endNames);
            }

        } else {
            // Handle new channel creation
            server.channels.push_back(Channel(channelName, "")); // addOperator
            idx = server.channels.size() - 1;
            server.channels[idx].addClientToChannel(server.clients[index]);
            server.channels[idx].setName(channelName);
            server.channels[idx].addOperator(server.clients[index].getNickName());

            // Notify the client about joining the new channel
            std::string channelinfo = ":" + server.clients[index].getNickName() + "!" + server.clients[index].getUserName() + " JOIN " + channelName;
            server.send_reply(server.clients[index].getClientFd(), channelinfo);

            // Send names list to the client
            std::string namesList = ":zaba.org 353 " + server.clients[index].getNickName() + " = " + channelName + " :@" + server.clients[index].getNickName();
            server.send_reply(server.clients[index].getClientFd(), namesList);
            std::cout << "JOIN : namesList: " << namesList << std::endl;

            // Send end of names list to the client
            std::string endNames = ":zaba.org 366 " + server.clients[index].getNickName() + " " + channelName + " :End of /NAMES list.";
            server.send_reply(server.clients[index].getClientFd(), endNames);
        }
    } else {
        server.send_reply(server.clients[index].getClientFd(), "JOIN : ERR_NOSUCHCHANNEL :No such channel");
    }
}
