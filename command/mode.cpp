#include "command.hpp"

void mode(my_server& server, int index) {
    if (server.input.size() == 2) {
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
            server.channels[idx].setMode(mode);
            for (size_t i = 0; i < server.channels[idx].getUsers().size(); ++i) {
                if (server.channels[idx].getUsers()[i].getNickName() == server.clients[index].getNickName()) {
                    found = true;
                    break;
                }
            }
            if (found == false) {
                server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_NOTONCHANNEL :You're not on that channel");
                return;
            }
            else if (server.channels[idx].isOperator(server.clients[index]) == false) {
                server.send_reply(server.clients[index].getClientFd(), "MODE : ERR_CHANOPRIVSNEEDED :You're not a channel operator");
                return;
            }
            else {
                 if (mode == "t") {
                    if (add_remove == "+") {
                        server.channels[idx].setTopicRestricted(true);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                    } else if (add_remove == "-") {
                        server.channels[idx].setTopicRestricted(false);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                    }
                } else if (mode == "i") {
                    if (add_remove == "+") {
                        server.channels[idx].setInviteOnly(true);
                        server.send_reply(server.clients[index].getClientFd(), ":zaba.org 324 " + server.clients[index].getNickName() + " " + server.channels[idx].getName() + " +" + mode);
                    } else if (add_remove == "-") {
                        server.channels[idx].setInviteOnly(false);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                    }
                } else if (mode == "l") {
                    if (add_remove == "+") {
                        server.channels[idx].setLimited(true, std::atoi(argOfTheMode.c_str()));
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                    } else if (add_remove == "-") {
                        server.channels[idx].setLimited(false, 0);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                    }
                } else if (mode == "o") {
                    if (add_remove == "+") {
                        server.channels[idx].addOperator(argOfTheMode);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                        std::string namesList = ":zaba.org 353 " + server.clients[index].getNickName() + " = " + channelName + " :";
                        for (size_t i = 0; i < server.channels[idx].getUsers().size(); ++i) {
                            if (i > 0) {
                                namesList += " ";
                            }
                            if (server.channels[idx].isOperator(server.channels[idx].getUsers()[i])) {
                                namesList += "@" + server.channels[idx].getUsers()[i].getNickName();
                            }
                            else
                                namesList += server.channels[idx].getUsers()[i].getNickName();
                            // namesList += "@" + server.channels[idx].getOperators()[i].getNickName();
                        }

                        std::string endNames = ":zaba.org 366 " + server.clients[index].getNickName() + " " + channelName + " :End of /NAMES list.";

                        for (size_t i = 0; i < server.channels[idx].getUsers().size(); ++i) {
                            server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), namesList);
                            server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), endNames);
                        }
                    } else if (add_remove == "-") {
                        server.channels[idx].removeOperator(argOfTheMode);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");

                        std::string namesList = ":zaba.org 353 " + server.clients[index].getNickName() + " = " + channelName + " :";

                        for (size_t i = 0; i < server.channels[idx].getUsers().size(); ++i) {
                            if (i > 0) {
                                namesList += " ";
                            }
                            if (server.channels[idx].isOperator(server.channels[idx].getUsers()[i])) {
                                namesList += "@" + server.channels[idx].getUsers()[i].getNickName();
                            }
                            else
                                namesList += server.channels[idx].getUsers()[i].getNickName();
                        }

                        std::string endNames = ":zaba.org 366 " + server.clients[index].getNickName() + " " + channelName + " :End of /NAMES list.";
                        
                        for (size_t i = 0; i < server.channels[idx].getUsers().size(); ++i) {
                            server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), namesList);
                            server.send_reply(server.channels[idx].getUsers()[i].getClientFd(), endNames);
                        }
                    }
                } else if (mode == "k")  {
                    if (add_remove == "+") {
                        server.channels[idx].setHavePassword(true);
                        server.channels[idx].setPassword(argOfTheMode);
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
                    } else if (add_remove == "-") {
                        server.channels[idx].setHavePassword(false);
                        server.channels[idx].setPassword("");
                        server.send_reply(server.clients[index].getClientFd(), "MODE :You have set the mode of the channel");
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
