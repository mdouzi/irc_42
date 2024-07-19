#include "command.hpp"
void privmsg(my_server& server, int index) {
    bool found = false;
    bool userFound = false;
    int channelIndex = 0;

    if (server.input.size() < 3) {
        server.send_reply(server.clients[index].getClientFd(), "PRIVMSG : ERR_NEEDMOREPARAMS :Not enough parameters");
        return;
    } else {
        std::string sender = server.clients[index].getNickName();
        std::string receiver = server.input[1];
        std::string message;
        bool friends = false;

        for (size_t i = 2; i < server.input.size(); i++) {
            message += server.input[i] + " ";
        }
        if (!message.empty()) {
            message.erase(message.size() - 1); // Remove trailing space
        }

        if (receiver[0] == '#') {
            // Handle channel message
            for (size_t i = 0; i < server.channels.size(); i++) {
                if (server.channels[i].getName() == receiver) {
                    found = true;
                    channelIndex = i;
                    break;
                }
            }
                for (size_t j = 0; j < server.channels[channelIndex].getUsers().size(); j++) {
                    if (server.channels[channelIndex].getUsers()[j].getNickName() == sender) {
                        userFound = true;
                        break;
                    }
                }
            if (found) {
                if (!userFound) {
                    server.send_reply(server.clients[index].getClientFd(), "PRIVMSG : ERR_NOTONCHANNEL :You're not on that channel");
                    return;
                }
                server.channels[channelIndex].sendMessageToChannel(server, message, index);
            } else {
                server.send_reply(server.clients[index].getClientFd(), "PRIVMSG : ERR_NOSUCHCHANNEL :No such channel");
            }
        } else {
            // Handle direct message
            int recIndex = 0;
            for (size_t i = 0; i < server.clients.size(); i++) {
                if (server.clients[i].getNickName() == receiver) {
                    found = true;
                    recIndex = i;
                    break;
                }
            }
            if (found) {
                // Check for previous conversation
                std::map<std::string, std::vector<std::string> >::iterator it = server.conversations.find(sender);
                if (it != server.conversations.end()) {
                    std::vector<std::string>::iterator vecIt;
                    for (vecIt = it->second.begin(); vecIt != it->second.end(); ++vecIt) {
                        if (*vecIt == receiver) {
                            friends = true;
                            break;
                        }
                    }
                }

                if (!friends) {
                    // New conversation
                    server.conversations[sender].push_back(receiver);
                    server.conversations[receiver].push_back(sender); // Assuming bi-directional conversation
                    server.send_reply(server.clients[recIndex].getClientFd(), ":" + sender + "!" + sender + "@0.0.0.0" + " PRIVMSG " + receiver + " :" + message);
                    server.send_reply(server.clients[index].getClientFd(), "PRIVMSG " + receiver + " :" + message);
                } else {
                    // Existing conversation
                    server.send_reply(server.clients[recIndex].getClientFd(), ":" + sender + "!" + sender + "@0.0.0.0" + " PRIVMSG " + receiver + " :" + message);
                }
            } else {
                server.send_reply(server.clients[index].getClientFd(), "PRIVMSG : ERR_NOSUCHNICK :No such nickname");
            }
        }
    }
}