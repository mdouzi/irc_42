#include "command.hpp"

// void kick(my_server& server, int index) {
//     if (server.clients[index].registered == false) {
//         server.send_reply(451, index, "You have not registered");
//         return;
//     }
//     if (server.channels[index].isOperator(server.clients[index]) == falsed ) {
//         server.send_reply(server.clients[index].getClientFd(), "You're not a channel operator");
//         return;
//     }
//     std::string channel = server.clients[index].channel;
//     std::string target = server.clients[index].target;
//     if (channel == "") {
//         server.send_reply(442, index, "You're not on a channel");
//         return;
//     }
//     if (target == "") {
//         server.send_reply(441, index, "No target specified");
//         return;
//     }
//     if (server.channels[channel].clients.find(target) == server.channels[channel].clients.end()) {
//         server.send_reply(441, index, "Target not on channel");
//         return;
//     }
//     if (server.clients[index].nick == target) {
//         server.send_reply(465, index, "You can't kick yourself");
//         return;
//     }
//     server.channels[channel].clients[target].send_reply(441, index, "You have been kicked by " + server.clients[index].nick);
//     server.channels[channel].clients[target].channel = "";
//     server.channels[channel].clients.erase(target);
//     server.send_reply(441, index, "Kicked " + target + " from " + channel);
//     server.send_to_channel(channel, ":" + server.clients[index].nick + "!" + server.clients[index].username + "@" + server.clients[index].hostname + " KICK " + channel + " " + target + " :Kicked by " + server.clients[index].nick);
// }