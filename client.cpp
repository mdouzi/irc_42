#include "client.hpp"

client::client() 
    : client_fd(-1), 
      realname(""), 
      username(""), 
      hostname(""), 
      servername(""), 
      nickname(""),  
      Alreadyregistred(false), 
      isAuthenticated(false) {}

client::~client() {}

void client::setClientFd(int fd) {
    client_fd = fd;
}

void client::setNickName(std::string const & str) {
    nickname = str;
}

void client::setRealName(std::string const & str) {
    realname = str;
}

void client::setHostName(std::string const & str) {
    hostname = str;
}

void client::setServerName(std::string const & str) {
    servername = str;
}

void client::setUserName(std::string const & str) {
    username = str;
}

void client::setAuth(bool of) {
    isAuthenticated = of;
}

void client::setReg(bool of) {
    Alreadyregistred = of;
}

std::string const &client::getNickName() {
    return nickname;
}

std::string const &client::getRealName() {
    return realname;
}

std::string const &client::getHostName() {
    return hostname;
}

std::string const &client::getServerName() {
    return servername;
}

std::string const &client::getUserName() {
    return username;
}

bool client::getAuth() {
    return isAuthenticated;
}

bool client::getReg() {
    return Alreadyregistred;
}

int client::getClientFd() {
    return client_fd;
}
