#include "command.hpp"

void privmsg(my_server& server, int index) {
    bool found = false;
    int idx = 0;
    if (server.input.size() < 3) {
        server.send_reply(server.clients[index].getClientFd(), "PRIVMSG : ERR_NEEDMOREPARAMS :Not enough parameters");
        return;
    } else if (server.input.size() >= 3) {
        std::string receiver = server.input[1];
        std::string message = server.clients[index].getNickName() + " SENDING MESSAGE TO CHANNEL " + server.channels[idx].getName() + " ";
        for (size_t i = 2; i < server.input.size(); i++) {
            message += server.input[i];
        }
        if (receiver[0] == '#') {
            for (size_t i = 0; i < server.channels.size(); ++i) {
                if (server.channels[i].getName() == receiver) {
                    found = true;
                    index = i;
                    break;
                }
            }
            if (found) {
                server.channels[idx].sendMessageToChannel(server, message);
                std::cout << "PRIVMSG command executed" << std::endl;
                std::cout << "Client " << server.clients[index].getClientFd() << " sent message to channel " << server.channels[idx].getName() << std::endl;
            } else {
                server.send_reply(server.clients[index].getClientFd(), "PRIVMSG : ERR_NOSUCHCHANNEL :No such channel");
            }
        } else {
            for (size_t i = 0; i < server.clients.size(); ++i) {
                if (server.clients[i].getNickName() == receiver) {
                    found = true;
                    index = i;
                    break;
                }
            }
            if (found) {
                server.clients[index].sendMessageToClient(server.clients[index], message);
                std::cout << "PRIVMSG command executed" << std::endl;
                std::cout << "Client " << server.clients[index].getNickName() << " sent message to client " << server.clients[index].getNickName() << std::endl;
            } else {
                server.send_reply(server.clients[index].getClientFd(), "PRIVMSG : ERR_NOSUCHNICK :No such nickname");
            }
        }
    }
}
