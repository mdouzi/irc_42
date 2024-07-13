#include "command.hpp"

// Function to handle the TOPIC command
void topic(my_server& server, int index) {
    if (server.input.size() < 2) {
        server.send_reply(server.clients[index].getClientFd(), "TOPIC : ERR_NEEDMOREPARAMS :Not enough parameters");
        return;
    }

    std::string channelName = server.input[1];
    std::string newTopic = "";
    for (size_t i = 2; i < server.input.size(); ++i) {
        newTopic += server.input[i];
        if (i != server.input.size() - 1) {
            newTopic += " ";
        }
    }
    std::cout << "channelName: " << channelName << std::endl;
    std::cout << "newTopic: " << newTopic << std::endl;

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
            server.send_reply(server.clients[index].getClientFd(), "TOPIC : ERR_NOTONCHANNEL :You're not on that channel");
            return;
        }
        else if (server.input.size() == 2){
            server.send_reply(server.clients[index].getClientFd(), "TOPIC " + channelName + " " + server.channels[idx].getTopic());
            return;
        }
        else if (server.channels[idx].getTopicRestricted() == true && server.channels[idx].isOperator(server.clients[index]) == false) {
            server.send_reply(server.clients[index].getClientFd(), "TOPIC : ERR_CHANOPRIVSNEEDED :You're not a channel operator");
            return;
        }
        else if (server.channels[idx].getTopicRestricted() == false && server.channels[idx].isOperator(server.clients[index]) == true) {
            if (server.channels[idx].getTopic() == "") {
                server.channels[idx].setTopic(newTopic);
                std::string topicMessage = ":" + server.clients[index].getNickName() + "!" + server.clients[index].getUserName() + " TOPIC " + channelName + " :" + newTopic;
                for (size_t i = 0; i < server.channels[idx].getUsers().size(); ++i) {
                    server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), topicMessage);
                }
            }
        }
    } else {
        server.send_reply(server.clients[index].getClientFd(), "TOPIC : ERR_NOSUCHCHANNEL :No such channel");
    }
}