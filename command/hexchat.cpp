#include "command.hpp"

void hexchat(my_server& server, int index) {
  std::cout << "Command received: HEXCHAT\n";
  index += 0;
if (2 < server.input.size()) {
    server.input.erase(server.input.begin(), server.input.begin() + 2);
  }
  std::cout << "hereeee  HEX" << server.input[0] << std::endl;
  std::cout << "hereeee  HEX" << server.input[1] << std::endl;
}