#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../server.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

void pass(my_server& server, int index);
void user(my_server& server, int index);
void nick(my_server& server, int index);
#endif 
