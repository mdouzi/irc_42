#include "command.hpp"

void send_reply(int cfd, std::string const & message) {
    std::string reply = message + "\r\n";
    ssize_t bytes_sent = send(cfd, reply.c_str(), reply.length(), 0);
    if (bytes_sent == -1) {
        std::cerr << "Error sending reply: " << strerror(errno) << std::endl;
    }
}

void kick(my_server & server, int index) {
    std::string channelName;
    std::string userName;
    std::string reason;
    int channelIndex;

    // Check and extract channel name
    if (server.input.size() > 1 && server.input[1][0] == '#' && server.input[1].size() > 1) {
        channelName = server.input[1];
        channelName.erase(0, channelName.find_first_not_of(" \t\n\r\f\v")); 
        channelName.erase(channelName.find_last_not_of(" \t\n\r\f\v") + 1); 
    } else {
        send_reply(server.clients[index].getClientFd(), "KICK : ERR_NOSUCHCHANNEL :No such channel");
        return;
    }

    // Check and extract user name
    if (server.input.size() > 2 && server.input[2].size() > 1) {
        userName = server.input[2];
        userName.erase(0, userName.find_first_not_of(" \t\n\r\f\v")); 
        userName.erase(userName.find_last_not_of(" \t\n\r\f\v") + 1); 
    } else {
        send_reply(server.clients[index].getClientFd(), "KICK : ERR_NOSUCHNICK :No such nick/channel");
        return;
    }

    // Check and extract reason (optional)
    if (server.input.size() > 3 && server.input[3][0] == ':') {
        reason = server.input[3].substr(1);
        for (size_t i = 5; i < server.input.size(); ++i) {
            reason += " " + server.input[i];
        }
    } else {
        reason = "";
    }

    // Find the channel
    if (!server.findChannel(channelName)) {
        send_reply(server.clients[index].getClientFd(), "KICK : ERR_NOSUCHCHANNEL :No such channel");
        return;
    } else {
        channelIndex = server.getChannel(channelName);
        if (channelIndex == -1) {
            send_reply(server.clients[index].getClientFd(), "KICK : ERR_NOSUCHCHANNEL :No such channel");
            return;
        }

        // Check if the client is a channel operator
        if (!server.channels[channelIndex].isOperator(server.clients[index])) {
            send_reply(server.clients[index].getClientFd(), "KICK : ERR_CHANOPRIVSNEEDED :You're not channel operator");
            return;
        } else {
            // Check if the user to be kicked is a member of the channel
            if (server.channels[channelIndex].isMember(userName)) {
                server.channels[channelIndex].deleteUser(userName);
                // Notify all members in the channel about the kick
                std::string kickMessage = ":" + server.clients[index].getNickName() + " KICK " + channelName + " " + userName;
                if (!reason.empty()) {
                    kickMessage += " :" + reason;
                }
                server.channels[channelIndex].broadcast(kickMessage);
                send_reply(server.clients[index].getClientFd(), "USER BEEN KICKED");
            } else {
                send_reply(server.clients[index].getClientFd(), "KICK : ERR_USERNOTINCHANNEL :They aren't on that channel");
                return;
            }
        }
    }
}

// for hexchat (+1 arg (network name))
void kick_hex(my_server & server, int index) {
    std::string channelName;
    std::string userName;
    std::string reason;
    int channelIndex;

    //kick netwrokname d#channelname username :reason 
    // Check and extract channel name
    if (server.input.size() > 1 && server.input[2][0] == '#' && server.input[2].size() > 1) {
        channelName = server.input[2];
        channelName.erase(0, channelName.find_first_not_of(" \t\n\r\f\v"));
        channelName.erase(channelName.find_last_not_of(" \t\n\r\f\v") + 1);
    } else {
        send_reply(server.clients[index].getClientFd(), "KICK : ERR_NOSUCHCHANNEL :No such channel");
        return;
    }

    // Check and extract user name
    if (server.input.size() > 2 && server.input[3].size() > 1) {
        userName = server.input[3].substr(1);
        userName.erase(0, userName.find_first_not_of(" \t\n\r\f\v"));
        userName.erase(userName.find_last_not_of(" \t\n\r\f\v") + 1);
    } else {
        send_reply(server.clients[index].getClientFd(), "KICK : ERR_NOSUCHNICK :No such nick/channel");
        return;
    }

    // Check and extract reason (optional)
    if (server.input.size() > 3 && server.input[4][0] == ':') {
        reason = server.input[4].substr(1);
        for (size_t i = 5; i < server.input.size(); ++i) {
            reason += " " + server.input[i];
        }
    } else {
        reason = "";
    }

    // Find the channel
    if (!server.findChannel(channelName)) {
        send_reply(server.clients[index].getClientFd(), "KICK : ERR_NOSUCHCHANNEL :No such channel");
        return;
    } else {
        channelIndex = server.getChannel(channelName);
        if (channelIndex == -1) {
            send_reply(server.clients[index].getClientFd(), "KICK : ERR_NOSUCHCHANNEL :No such channel");
            return;
        }

        // Check if the client is a channel operator
        if (!server.channels[channelIndex].isOperator(server.clients[index])) {
            send_reply(server.clients[index].getClientFd(), "KICK : ERR_CHANOPRIVSNEEDED :You're not channel operator");
            return;
        } else {
            // Check if the user to be kicked is a member of the channel
            if (server.channels[channelIndex].isMember(userName)) {
                server.channels[channelIndex].deleteUser(userName);
                // Notify all members in the channel about the kick
                std::string kickMessage = ":" + server.clients[index].getNickName() + " KICK " + channelName + " " + userName;
                if (!reason.empty()) {
                    kickMessage += " :" + reason;
                }
                server.channels[channelIndex].broadcast(kickMessage);
                send_reply(server.clients[index].getClientFd(), "USER BEEN KICKED");
            } else {
                send_reply(server.clients[index].getClientFd(), "KICK : ERR_USERNOTINCHANNEL :They aren't on that channel");
                return;
            }
        }
    }
}