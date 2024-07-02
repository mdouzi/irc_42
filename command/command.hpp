#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../server.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include "../Channel.hpp"
#include "../client.hpp"

void pass(my_server& server, int index);
void user(my_server& server, int index);
void nick(my_server& server, int index);
void join(my_server& server, int index);
void privmsg(my_server& server, int index);
void mode(my_server& server, int index);
void hexchat(my_server& server, int index);
#endif 
