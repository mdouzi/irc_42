#include "command.hpp"
#include "../client.hpp"

void send_reply_pass(int cfd, std::string const & message)
{
   std::string reply = message + "\r\n";
  ssize_t bytes_sent = send(cfd, reply.c_str(), reply.length(), 0);
  if (bytes_sent == -1) {  
    std::cerr << "Error sending reply: " << strerror(errno) << std::endl;
  }
}


void pass(my_server& server, int index) {
	if(server.input.size() < 2)
	{
		send_reply_pass(server.clients[index].getClientFd(), "----->  Incorrect password !! <-----");
	} else if (!strncmp(server.input[1].c_str(), server.getPassword().c_str(), server.getPassword().size())){
		send_reply_pass(server.clients[index].getClientFd() , "------>   Welcome ;D  <------ ");
		server.clients[index].setAuth(true);
		if (2 < server.input.size()) {
            server.input.erase(server.input.begin(), server.input.begin() + 2);
        }
	}
	else {
		send_reply_pass(server.clients[index].getClientFd(), "----->  Incorrect password !! <-----");
	}
}
