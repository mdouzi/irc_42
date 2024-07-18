#include "command.hpp"

void list(my_server &server, int index) {
    if (server.input.size() != 1) {
        server.send_reply(server.clients[index].getClientFd(), "LIST : ERR_NEEDMOREPARAMS :Not enough parameters");
        return;
    } else {
        server.send_reply(server.clients[index].getClientFd(), ":zaba.irc.com 321 " + server.clients[index].getNickName() + " Channel :Users  Name");
        for (size_t i = 0; i < server.channels.size(); i++) {
            std::string hex_info = ":zaba.irc.com 322 " + server.clients[index].getNickName() + " " + server.channels[i].getName() + " " + std::to_string(server.channels[i].getUsers().size()) + " :[+ntz] " + server.channels[i].getTopic();
            server.send_reply(server.clients[index].getClientFd(), hex_info);
        }
        server.send_reply(server.clients[index].getClientFd(), ":zaba.irc.com 323 " + server.clients[index].getNickName() + " :End of /LIST");
    }
}
