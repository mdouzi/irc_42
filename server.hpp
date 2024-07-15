#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <poll.h>
#include <map>
#include <cstdint>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "client.hpp"
#include "Channel.hpp"

#define MAX_CLIENTS 4096



class client;
class Channel;

class my_server {
	private:
            std::string _password;
		std::vector<pollfd> _mypolls;
            std::map<int, bool> _disconnectedClients;
	public:
      std::map<std::string, std::vector<std::string> > conversations;
      std::vector<client> clients;
      std::vector<Channel> channels;
      std::vector<std::string> input;
      my_server();
      ~my_server();
      void send_reply(int cfd, std::string const & message);
      void runServer(wint_t port);
      void handleClientCommands(int cfd, int index);
      void SplitInput(char buffer[255], std::vector<std::string> &tokens);

      void setPassword(std::string const & password);


      bool findChannel(std::string const &ChannelName);
      bool isUserOnChannel(std::string const &ChannelName, std::string const &ClientName);
      
      std::string const & getPassword() const;
};



#endif
