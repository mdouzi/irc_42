#include "Channel.hpp"
#include <sys/types.h>
#include <sys/socket.h>

Channel::Channel() {
}

Channel::Channel(std::string name, std::string topic, client op, std::string password)
    : name(name), topic(topic), password(password) {
    operators.push_back(op);
}

Channel::Channel(std::string name, std::string topic)
    : name(name), topic(topic) {
        _isInviteOnly = false;
        _isLimited = false;
        _isTopicRestricted = false;
        _limit = 0;
}

Channel::~Channel() {
}

bool Channel::getTopicRestricted() {
    return _isTopicRestricted;
}

std::string const & Channel::getMode() const {
    return mode;
}

std::string const & Channel::getName() const {
    return name;
}

std::string const & Channel::getTopic() const {
    return topic;
}

std::string const & Channel::getPassword() const {
    return password;
}


std::vector<client> & Channel::getUsers() {
    return users;
}


bool Channel::isInvited(client newClient) {
    for (size_t i = 0; i < invited.size(); ++i) {
        if (invited[i].getNickName() == newClient.getNickName()) {
            return true;
        }
    }
    return false;
}


void Channel::setHavePassword(bool havePassword) {
    _havePassword = havePassword;
}

bool Channel::isHavePassword() {
    return _havePassword;
}


bool Channel::isInviteOn() {
    return _isInviteOnly;
}


void Channel::setInvitedClients(client newClient) {
    invited.push_back(newClient);
}


void Channel::setLimited(bool isLimited, int limit) {
    _isLimited = isLimited;
    _limit = limit;
}

void Channel::setTopicRestricted(bool isTopicRestricted) {
    _isTopicRestricted = isTopicRestricted;
}

size_t Channel::getLimit() const {
    return _limit;
}

void Channel::setMode(std::string const & str) {
    mode = str;
}

void Channel::setInviteOnly(bool isInviteOnly) {
    _isInviteOnly = isInviteOnly;
}

void Channel::setName(std::string const & str) {
    name = str;
}

void Channel::setTopic(std::string const & str) {
    topic = str;
}

void Channel::setPassword(std::string const & str) {
    password = str;
}

void Channel::addClientToChannel(const client newClient) {
    this->users.push_back(newClient);
}

void Channel::sendMessageToChannel(my_server& server, std::string message, int index) {
    std::string messageToSend = ":" + server.clients[index].getNickName() + "!" + server.clients[index].getUserName() + " PRIVMSG " + this->name + " :" + message;

    for (size_t i = 0; i < this->users.size(); ++i) {
        if (this->users[i].getNickName() != server.clients[index].getNickName()) {
            server.send_reply(this->users[i].getClientFd(), messageToSend);
        }
    
    }
}


void Channel::removeOperator(std::string newClient) {
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i].getNickName() == newClient) {
            operators.erase(operators.begin() + i);
            break;
        }
    }
}

void Channel::deleteUser(std::string const & userName)
{
  for(std::vector<client>::iterator it = this->users.begin(); it != this->users.end(); it++) {
    if(it->getNickName() == userName) {
      this->users.erase(it);;
      return;
    }
  }

  for(std::vector<client>::iterator it1 = this->operators.begin(); it1 != this->operators.end(); it1++) {
    if(it1->getNickName() == userName) {
      this->operators.erase(it1);
      return;
    }
  }
}

void Channel::addOperator(std::string newClient) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].getNickName() == newClient) {
            operators.push_back(users[i]);
            break;
        }
    }

}

bool Channel::isOperator(client newClient) {
     for (size_t i = 0; i < operators.size(); ++i) {
         if (operators[i].getNickName() == newClient.getNickName()) {
           return true;
        }
     }
     return false;
}

std::vector<client> & Channel::getOperators() {
    return operators;
}

bool Channel::isMember(std::string const & ClientName) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].getNickName() == ClientName) {
            return true;
        }
    }
    return false;
}


void Channel::send_reply(int cfd, std::string const & message) {
    std::string reply = message + "\r\n";
    ssize_t byte_sent  = send(cfd, reply.c_str(), reply.length(), 0);
    if(byte_sent == -1) {
        std::cerr << "Error sending reply: " << strerror(errno) << std::endl;
    }
}

 void Channel::broadcast(std::string message) {
     for (size_t i = 0; i < users.size(); ++i) {
        send_reply(this->users[i].getClientFd(), message);
     }

     for(size_t j = 0; j < operators.size(); ++j) {
        send_reply(this->operators[j].getClientFd(), message);
     }
}




