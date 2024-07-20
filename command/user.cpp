#include "command.hpp"
#include "../client.hpp"

std::string intToString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

void send_reply_user(int cfd, std::string const & message)
{
   std::string reply = message + "\r\n";
  ssize_t bytes_sent = send(cfd, reply.c_str(), reply.length(), 0);
  if (bytes_sent == -1) {  
    std::cerr << "Error sending reply: " << strerror(errno) << std::endl;
  }
}


void user(my_server &server, int index) {
    if (server.input.size() < 5) {
        send_reply_user(server.clients[index].getClientFd(), "ERROR: USER <username> <hostname> <servername> <realname>\n");
        server.clients[index].setReg(false);
    } else {
        if (server.input[1].length() > USERLEN) {
            send_reply_user(server.clients[index].getClientFd(), "ERROR: Maximum USERLEN is " + intToString(USERLEN) + "\n");
        }
        server.clients[index].setUserName(server.input[1]);
		server.clients[index].setHostName(server.input[2]);
        server.clients[index].setServerName(server.input[3]);
		std::string tempRealName = server.input[4] + " ";
        if (server.input.size() > 5) {
            tempRealName += server.input[5];
        }
        server.clients[index].setRealName(tempRealName);
        send_reply_user(server.clients[index].getClientFd() , "----> USER COMMAND SUCCESSFUL <----");
        if (2 < server.input.size()) {
            server.input.erase(server.input.begin(), server.input.begin() + 2);
        }
    }
}

