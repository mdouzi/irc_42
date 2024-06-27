#include "command.hpp"

void mode(my_server& server, int index) {
    if (server.input.size() <= 2) {
        server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_NEEDMOREPARAMS :Not enough parameters");
        return;
    } else if (server.input.size() == 3 || server.input.size() == 4) {

        std::string channelName = server.input[1];
        std::string add_remove = std::string(1, server.input[2][0]);
        std::string mode = std::string(1, server.input[2][1]);
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
            if (server.channels[idx].isMember(server.clients[idx].getNickName()) == false) {
                server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_NOTONCHANNEL :You're not on that channel");
                return;
            }
            else if (server.channels[idx].isOperator(server.clients[index]) == false) {
                server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_CHANOPRIVSNEEDED :You're not a channel operator");
                return;
            }
            else {
                if (mode == "i") {
                    if (add_remove == "+") {
                        server.channels[idx].setInviteOnly(true);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
                    } else if (add_remove == "-") {
                        server.channels[idx].setInviteOnly(false);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
                    }
                } else if (mode == "t") {
                    if (add_remove == "+") {
                        server.channels[idx].setTopicRestricted(true);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
                    } else if (add_remove == "-") {
                        server.channels[idx].setTopicRestricted(false);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
                    }
                } else if (mode == "l") {
                    if (add_remove == "+") {
                        server.channels[idx].setLimited(true, std::atoi(argOfTheMode.c_str()));
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
                    } else if (add_remove == "-") {
                        server.channels[idx].setLimited(false, 0);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
                    }
                } else if (mode == "o") {
                    if (add_remove == "+") {
                        server.channels[idx].addOperator(server.clients[index]);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
                    } else if (add_remove == "-") {
                        server.channels[idx].removeOperator(server.clients[index]);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
                    }
                } else if (mode == "k")  {
                    if (add_remove == "+") {
                        server.channels[idx].setPassword(argOfTheMode);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
                    } else if (add_remove == "-") {
                        server.channels[idx].setPassword("");
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::cout << "Client " << server.clients[index].getNickName() << " set the mode of channel " << server.channels[idx].getName() << " to " << server.channels[idx].getMode() << std::endl;
                    }
                } else {
                    server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_UNKNOWNMODE :Unknown mode");
                }
            } 
        } else {
                server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_NOSUCHCHANNEL :No such channel");
            }
    } else {
            server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_NEEDMOREPARAMS :Not enough parameters");
        }
}
